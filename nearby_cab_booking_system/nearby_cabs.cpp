// ============================================================================
//  Finding Nearby Cabs
//  ------------------------------------------------------------------------
//  Finds the nearest available cabs to a user's GPS location using the
//  Great-Circle (Haversine) distance formula.
//
//  Build:  g++ -std=c++17 -O2 nearby_cabs.cpp -o nearby_cabs
//  Run:    ./nearby_cabs cabs.csv
// ============================================================================

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static const double EARTH_RADIUS_KM = 6371.0088;
static const double PI = 3.14159265358979323846;

// ---------------------------------------------------------------------------
// Domain model (mirrors the `cabs` table in the DBMS)
// ---------------------------------------------------------------------------
struct Cab {
    int         id;
    std::string driver;
    std::string plate;
    std::string type;      // Mini / Sedan / SUV / EV
    double      lat;
    double      lon;
    bool        available;
    double      rating;
    double      farePerKm;  // used by the Payment Gateway module
};

struct Match {
    Cab    cab;
    double distanceKm;
    int    etaMinutes;
    double estimatedFare;
};

// ---------------------------------------------------------------------------
// Great-circle distance (Haversine formula)
//
//   a = sin^2(dLat/2) + cos(lat1) * cos(lat2) * sin^2(dLon/2)
//   c = 2 * atan2( sqrt(a), sqrt(1-a) )
//   d = R * c
// ---------------------------------------------------------------------------
inline double toRadians(double degrees) { return degrees * PI / 180.0; }

double greatCircleDistance(double lat1, double lon1, double lat2, double lon2) {
    const double dLat = toRadians(lat2 - lat1);
    const double dLon = toRadians(lon2 - lon1);

    const double a = std::sin(dLat / 2.0) * std::sin(dLat / 2.0) +
                     std::cos(toRadians(lat1)) * std::cos(toRadians(lat2)) *
                     std::sin(dLon / 2.0) * std::sin(dLon / 2.0);

    const double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
    return EARTH_RADIUS_KM * c;
}

// ---------------------------------------------------------------------------
// "DBMS layer": load the cab fleet from a CSV export of the cabs table.
// Replace this with a real MySQL/PostgreSQL connector in production.
// ---------------------------------------------------------------------------
std::vector<Cab> loadCabs(const std::string& path) {
    std::vector<Cab> cabs;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open " << path << " -- using built-in demo fleet.\n";
        return {
            {1, "Ravi Kumar",  "KA-01-AB-1234", "Sedan", 12.9784, 77.6408, true, 4.8, 18.0},
            {2, "Anita Desai", "KA-05-CJ-8821", "Mini",  12.9611, 77.6387, true, 4.6, 14.0},
            {3, "Imran Shah",  "KA-03-MK-4590", "SUV",   12.9345, 77.6101, true, 4.9, 24.0},
            {4, "Neha Rao",    "KA-02-HR-7712", "EV",    12.9982, 77.5921, true, 4.7, 16.0},
            {5, "Suresh P.",   "KA-04-QW-3345", "Sedan", 12.9250, 77.6800, false, 4.4, 18.0},
        };
    }

    std::string line;
    std::getline(file, line); // skip the header row
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string token;
        Cab c{};

        std::getline(ss, token, ','); c.id     = std::stoi(token);
        std::getline(ss, c.driver, ',');
        std::getline(ss, c.plate,  ',');
        std::getline(ss, c.type,   ',');
        std::getline(ss, token, ','); c.lat    = std::stod(token);
        std::getline(ss, token, ','); c.lon    = std::stod(token);
        std::getline(ss, token, ','); c.available = (token == "1" || token == "true");
        std::getline(ss, token, ','); c.rating = std::stod(token);
        std::getline(ss, token, ','); c.farePerKm = std::stod(token);

        cabs.push_back(c);
    }
    return cabs;
}

// ---------------------------------------------------------------------------
// Matching engine: rank every available cab by great-circle distance.
// ---------------------------------------------------------------------------
std::vector<Match> findNearestCabs(const std::vector<Cab>& cabs,
                                   double userLat, double userLon,
                                   std::size_t limit,
                                   double avgSpeedKmph = 24.0,
                                   double baseFare = 30.0) {
    std::vector<Match> matches;
    for (const Cab& cab : cabs) {
        if (!cab.available) continue;
        const double d = greatCircleDistance(userLat, userLon, cab.lat, cab.lon);
        Match m;
        m.cab           = cab;
        m.distanceKm    = d;
        m.etaMinutes    = static_cast<int>(std::ceil((d / avgSpeedKmph) * 60.0));
        m.estimatedFare = baseFare + d * cab.farePerKm;
        matches.push_back(m);
    }

    std::sort(matches.begin(), matches.end(),
              [](const Match& a, const Match& b) { return a.distanceKm < b.distanceKm; });

    if (matches.size() > limit) matches.resize(limit);
    return matches;
}

void printMatches(const std::vector<Match>& matches) {
    if (matches.empty()) {
        std::cout << "\nNo cabs are available near you right now.\n";
        return;
    }

    std::cout << "\n" << std::left
              << std::setw(4)  << "#"
              << std::setw(16) << "DRIVER"
              << std::setw(16) << "PLATE"
              << std::setw(8)  << "TYPE"
              << std::setw(12) << "DISTANCE"
              << std::setw(8)  << "ETA"
              << std::setw(10) << "FARE"
              << "LOCATION\n";
    std::cout << std::string(88, '-') << "\n";

    int rank = 1;
    for (const Match& m : matches) {
        std::ostringstream dist, eta, fare, loc;
        dist << std::fixed << std::setprecision(2) << m.distanceKm << " km";
        eta  << m.etaMinutes << " min";
        fare << "Rs " << std::fixed << std::setprecision(0) << m.estimatedFare;
        loc  << std::fixed << std::setprecision(4) << m.cab.lat << ", " << m.cab.lon;

        std::cout << std::left
                  << std::setw(4)  << rank++
                  << std::setw(16) << m.cab.driver
                  << std::setw(16) << m.cab.plate
                  << std::setw(8)  << m.cab.type
                  << std::setw(12) << dist.str()
                  << std::setw(8)  << eta.str()
                  << std::setw(10) << fare.str()
                  << loc.str() << "\n";
    }

    const Match& best = matches.front();
    std::cout << "\nNearest cab: " << best.cab.driver << " (" << best.cab.plate << ") is "
              << std::fixed << std::setprecision(2) << best.distanceKm
              << " km away, arriving in about " << best.etaMinutes << " minutes.\n";
}

int main(int argc, char** argv) {
    const std::string csvPath = (argc > 1) ? argv[1] : "cabs.csv";
    const std::vector<Cab> fleet = loadCabs(csvPath);

    double userLat = 0.0, userLon = 0.0;
    std::cout << "=========================================\n"
              << "        FINDING NEARBY CABS (C++)        \n"
              << "=========================================\n"
              << "Fleet loaded: " << fleet.size() << " cabs\n\n"
              << "Enter your latitude  : ";
    if (!(std::cin >> userLat)) { std::cerr << "Invalid latitude.\n"; return 1; }
    std::cout << "Enter your longitude : ";
    if (!(std::cin >> userLon)) { std::cerr << "Invalid longitude.\n"; return 1; }

    if (userLat < -90 || userLat > 90 || userLon < -180 || userLon > 180) {
        std::cerr << "Coordinates out of range.\n";
        return 1;
    }

    const std::vector<Match> matches = findNearestCabs(fleet, userLat, userLon, 5);
    printMatches(matches);
    return 0;
}
