#include <QCoreApplication>
#include <QProcessEnvironment>
#include <QVector>
#include <QSet>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QtMath>

const double THRESHOLD_DEFAULT = 0.001;
const int MULTIPLIER = 1000;
const QString WATER_PRESSURE_FILE_PATH_DEFAULT = "water_pressure_points.txt";

struct WaterPressurePoints
{
    double x;
    double y;
    double water_pressure;

    WaterPressurePoints(double x_ = 0.0, double y_ = 0.0, double w_ = 0.0)
        : x(x_), y(y_), water_pressure(w_)
    {
    }

    // Helper function to check whether the data point is valid or not
    bool isValid() const
    {
        return water_pressure >= 0.0;
    }

    /* Custom comparison operator with threshold
     *
     * Calculate the Euclidean distance between two data points
     * in coordinates, and compare the distance with threshold to
     * see if they are equal enough
    */
    bool operator==(const WaterPressurePoints& other) const
    {
        const double threshold = THRESHOLD_DEFAULT;
        double dx = x - other.x;
        double dy = y - other.y;
        double distance = std::sqrt(dx * dx + dy * dy);
        return distance < threshold;
    }

    // Overload << for QTextStream
    friend QTextStream& operator<<(QTextStream& stream, const WaterPressurePoints& point)
    {
        stream << point.x << " " << point.y << " ";

        // Write the orginal water pressure if the distance with rounded value small enough
        // Otherwise, write the formatted as rounded to 3 decimal places
        double rounded = std::round(point.water_pressure * MULTIPLIER) / MULTIPLIER;
        if (std::abs(point.water_pressure - rounded) < 1e-9)
        {
            stream << point.water_pressure;
        }
        else
        {
            stream << QString::number(rounded, 'f', 3);
        }

        stream << Qt::endl;
        return stream;
    }
};

inline uint qHash(const WaterPressurePoints& p, uint seed = 0)
{
    // Combine x and y to generate hash value
    return qHash(static_cast<int>(p.x * MULTIPLIER)) ^ qHash(static_cast<int>(p.y * MULTIPLIER), seed);
}

/*
 * Main process
 *   Maintain the processed data points using QSet
 *   Maintain the unique data points using QVector
 *   Walk through the data points
 *     Check if data is valid or not
 *     Check if the coordinate exists in the processed set
 *       If not, insert the coordinate into processed set and add data point into the filtered list
 *   Write the filtered list to the output file WATER_PRESSURE_FILE_PATH
 *
 * It works due to the benefit of overloaded operator== of WaterPressurePoints
 * that helps the QSet ignore the coordinates that are equal enough to the processed point
 *
*/
void WriteWaterPressure(std::vector<WaterPressurePoints>& points)
{
    if (points.empty())
    {
        qWarning() << "No data to process";
        return;
    }

    QSet<WaterPressurePoints> processed;
    QVector<WaterPressurePoints> filtered;

    for (const auto& point : points)
    {
        if (!point.isValid())
        {
            QString msg = QString("Skip invalid data point %1, %2, %3")
                    .arg(point.x)
                    .arg(point.y)
                    .arg(point.water_pressure);
            qWarning() << msg;
            continue;
        }

        if (!processed.contains(point))
        {
            processed.insert(point);
            filtered << point;
        }
    }

    // Open file for writing. Get WATER_PRESSURE_FILE_PATH from env
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    const QString filePath = env.value("WATER_PRESSURE_FILE_PATH", WATER_PRESSURE_FILE_PATH_DEFAULT);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open file for writing.";
        return;
    }

    QTextStream out(&file);
    for (const auto& i : filtered)
    {
        out << i;
    }

    file.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setOrganizationName("MaTruongAnh");
    app.setApplicationName("filteroutduplicate");

    {
        std::vector<WaterPressurePoints> points = {
            {0, 0, 0},              // First (0, 0)
            {0, 0, 15},             // Duplicate (0, 0)
            {1e-19, 0, 10},         // Duplicate (0, 0)
            {0.5, 0, 25.123},       // Unique
            {0.1, 10, 25},          // Unique
        };

        WriteWaterPressure(points);
        /* Expected
        0 0 0
        0.5 0 25.123
        0.1 10 25 */
    }

//    {
//        std::vector<WaterPressurePoints> points = {
//            {0, 0, 0},              // First (0, 0)
//            {0, 0, 15},             // Duplicate (0, 0)
//            {1e-19, 0, 10},         // Duplicate (0, 0)
//            {0.5, 0, 25.123},       // Unique
//            {0.1, 10, 25},          // Unique
//            {0.5, 0, -12.345},      // Invalid
//            {-1e-20, 0, 99.999},    // Duplicate (0, 0)
//            {0.1, 10, 0.001},       // Duplicate (0.1, 10)
//            {2.345, -3.456, 7.89},  // Unique
//            {-0.001, 5, 123.456}    // Unique
//        };

//        WriteWaterPressure(points);
//        /* Expected
//        0 0 0
//        0.5 0 25.123
//        0.1 10 25
//        2.345 -3.456 7.89
//        -0.001 5 123.456 */
//    }

//    {
//        std::vector<WaterPressurePoints> points = {
//            {0, 0, 0},              // First (0, 0)
//            {0.0001, 0, 1e-5},      // Duplicate (0, 0) (precision=3)
//            {1e-19, 0, 999.9999},   // Duplicate (0, 0)
//            {0.5, 0.5, 25.12345},   // Unique
//            {10, 10, 12345.6786},   // Unique
//            {0.5, 0.5, -0.0001},    // Invalid
//            {-0.00001, 0, 0.123},   // Duplicate (0, 0)
//            {1000, -1000, 0},       // Unique
//            {0, 0, 15.55555}        // Duplicate (0, 0)
//        };

//        WriteWaterPressure(points);
//        /* Expected
//        0 0 0
//        0.5 0.5 25.123
//        10 10 12345.679
//        1000 -1000 0 */
//    }

//    {
//        std::vector<WaterPressurePoints> points = {
//            {1.234, 5.678, 10},      // First (1.23, 5.68)
//            {1.2345, 5.6789, 20},    // Unique (precision=3)
//            {1.23, 5.67, 30},        // Unique (precision=3)
//            {1.235, 5.679, 40},      // Duplicate (1.23, 5.68)
//            {2.345, 6.789, 50},      // Unique
//            {2.34, 6.78, 60},        // Unique (precision=3)
//            {0, 0, 0},               // Unique
//            {0.001, 0.001, 15},      // Unique (precision=3)
//            {-1.23, -5.67, -25.123}  // Invalid
//        };

//        WriteWaterPressure(points);
//        /* Expected
//        1.234 5.678 10
//        1.2345 5.6789 20
//        1.23 5.67 30
//        2.345 6.789 50
//        2.34 6.78 60
//        0 0 0
//        0.001 0.001 15 */
//    }

//    {
//        std::vector<WaterPressurePoints> points = {
//            {0, 0, 0},              // First (0, 0)
//            {1e-10, 0, 1e-10},      // Duplicate (0, 0)
//            {-9999.999, 9999.999, -12345.6789}, // Invalid
//            {0, 0, 99999.9999},     // Duplicate (0, 0)
//            {0.12345, 0.6789, 0.001} // Unique
//        };

//        WriteWaterPressure(points);
//        /* Expected
//        0 0 0
//        0.12345 0.6789 0.001 */
//    }

//    {
//        std::vector<WaterPressurePoints> points = {
//            {1.23456, 2.34567, 15.6789},  // Unique
//            {1.2347, 2.3458, 20.1234},    // Duplicate (1.23456, 2.34567)
//            {1000.0, -1000.0, 0.0},       // Unique
//            {1000.0001, -1000.0001, 5.5}, // Duplicate (1000, -1000)
//            {-0.0005, 0.0005, 10.0},      // Unique
//            {0.0, 0.0, -1.23},            // Invalid
//            {1.5, 2.5, 999.999}           // Unique
//        };

//        WriteWaterPressure(points);
//        /* Expected
//        1.23456 2.34567 15.679
//        1000 -1000 0
//        -0.0005 0.0005 10
//        1.5 2.5 999.999 */
//    }

//    {
//        std::vector<WaterPressurePoints> points = {
//            {0.0001, 0.0001, 0.123},      // Unique
//            {0.0, 0.0, 5.0},              // Duplicate (0.0001, 0.0001)
//            {1e-5, 1e-5, 10.0},           // Duplicate (0.0001, 0.0001)
//            {-1e-5, -1e-5, 15.0},         // Duplicate (0.0001, 0.0001)
//            {0.0002, 0.0002, -0.001},     // Invalid
//            {0.001, 0.001, 20.0},         // Unique
//            {0.0, 0.0, 25.0}              // Duplicate (0.0001, 0.0001)
//        };

//        WriteWaterPressure(points);
//        /* Expected
//        0.0001 0.0001 0.123
//        0.001 0.001 20 */
//    }

//    {
//        std::vector<WaterPressurePoints> points = {
//            {5000.0, 5000.0, 1000.0},     // Unique
//            {5000.0005, 5000.0005, 2000.0}, // Duplicate (5000, 5000)
//            {5000.1, 5000.1, 3000.0},     // Unique
//            {4999.999, 4999.999, 4000.0}, // Duplicate (5000, 5000)
//            {5000.0, 5000.0, -5000.0},    // Invalid
//            {6000.0, 6000.0, 0.001}       // Unique
//        };

//        WriteWaterPressure(points);
//        /* Expected
//        5000 5000 1000
//        5000.1 5000.1 3000
//        6000 6000 0.001 */
//    }

//    {
//        std::vector<WaterPressurePoints> points = {
//            {-0.0001, 0.0, 0.0},          // Unique
//            {0.0, -0.0001, 1.0},          // Duplicate (-0.0001, 0.0)
//            {-1e-5, 0.0, 2.0},            // Duplicate (-0.0001, 0.0)
//            {0.0, 0.0, -1e-5},            // Invalid
//            {0.0, 0.0, 0.0},              // Duplicate (-0.0001, 0.0)
//            {-0.0002, 0.0, 3.0}           // Duplicate (-0.0001, 0.0)
//        };

//        WriteWaterPressure(points);
//        /* Expected
//        -0.0001 0 0 */
//    }

    return 0;
}
