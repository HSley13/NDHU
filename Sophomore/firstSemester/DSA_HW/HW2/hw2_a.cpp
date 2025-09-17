#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <vector>

struct Station {
    int id;
    std::string name;
    int totalEntries{0};
    int totalExits{0};
};

struct BookingRecord {
    int startID;
    int endID;
    int numberOfTickets;
};

class StationBookingSystem {
  public:
    StationBookingSystem(const std::string &stationFileName, const std::string &bookingFileName, const std::string &summaryFileName) {
        stationFile.open(stationFileName);
        if (!stationFile) {
            throw std::runtime_error("Error opening station file!");
        }

        bookingFile.open(bookingFileName);
        if (!bookingFile) {
            throw std::runtime_error("Error opening booking file!");
        }

        summaryFile.open(summaryFileName);
        if (!summaryFile) {
            throw std::runtime_error("Error opening summary file");
        }

        loadStationData();
        loadBookingData();
        generateSummary();
    }

  private:
    std::map<int, Station> stationMap;
    std::vector<BookingRecord> bookingRecords;
    std::ifstream stationFile, bookingFile;
    std::ofstream summaryFile;

    void loadStationData() {
        std::string line;
        while (std::getline(stationFile, line)) {
            std::istringstream ss(line);
            int id;
            std::string name;
            ss >> id >> name;

            Station station = {id, name, 0, 0};
            stationMap[id] = station;
        }
    }

    void loadBookingData() {
        std::string line;
        while (std::getline(bookingFile, line)) {
            std::istringstream ss(line);
            int startID, endID, numberOfTickets;
            ss >> startID >> endID >> numberOfTickets;

            BookingRecord record = {startID, endID, numberOfTickets};
            bookingRecords.push_back(record);

            if (stationMap.find(startID) != stationMap.end()) {
                stationMap[startID].totalEntries += numberOfTickets;
            }

            if (stationMap.find(endID) != stationMap.end()) {
                stationMap[endID].totalExits += numberOfTickets;
            }
        }
    }

    void generateSummary() {
        // **Part 1**: StationID, Stationname, total number of entries (sorted by StationName)
        std::vector<Station> stations;
        for (const std::pair<const int, Station> &pair : stationMap) {
            stations.push_back(pair.second);
        }

        std::sort(stations.begin(), stations.end(), [](const Station &a, const Station &b) {
            return a.name < b.name;
        });

        for (const Station &station : stations) {
            summaryFile << station.id << " " << station.name << " " << station.totalEntries << std::endl;
        }
        summaryFile << std::endl;

        // **Part 2**: StationID, Stationname, total number of exits (sorted by totalExits in increasing order)
        std::sort(stations.begin(), stations.end(), [](const Station &a, const Station &b) {
            return a.totalExits < b.totalExits;
        });

        for (const Station &station : stations) {
            summaryFile << station.id << " " << station.name << " " << station.totalExits << std::endl;
        }
        summaryFile << std::endl;

        // **Part 3**: Source name, Destination name, total passengers (for each source-destination pair)
        std::map<std::pair<std::string, std::string>, int> sourceDestinationMap;

        for (const BookingRecord &record : bookingRecords) {
            const std::string &sourceName{stationMap[record.startID].name};
            const std::string &destName{stationMap[record.endID].name};
            std::pair<std::string, std::string> route = {sourceName, destName};

            sourceDestinationMap[route] += record.numberOfTickets;
        }

        for (const std::pair<const std::pair<std::string, std::string>, int> &pair : sourceDestinationMap) {
            summaryFile << pair.first.first << " " << pair.first.second << " " << pair.second << std::endl;
        }

        std::cout << "Done!" << std::endl;
    }
};

int main(void) {
    try {
        StationBookingSystem system("DataStructureHW/HW2/station_name.txt", "DataStructureHW/HW2/booking_record.txt", "DataStructureHW/HW2/summary.txt");
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
