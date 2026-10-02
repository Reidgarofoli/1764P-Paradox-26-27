#include <iostream>
#include <fstream>
#include <istream>

// logger class that will write to a file called "log.txt"
class Logger {
    public:
        Logger() {
            logfile.open("/usd/log.txt");
            if (!logfile.is_open()) {
                std::cerr << "Failed to open log file: log.txt" << std::endl;
            }
        }

        void close() {
            if (logfile.is_open()) {
                logfile.close();
            }
        }

        ~Logger() {
            if (logfile.is_open()) {
                logfile.close();
            }
        }

        void log(const std::string& message) {
            if (logfile.is_open()) {
                logfile << message << std::endl;
            }
        }

        std::string readLine(int lineNumber) {
            std::ifstream readLogfile("/usd/log.txt");
            if (readLogfile.is_open()) {
                readLogfile.clear(); // Clear any EOF flags
                readLogfile.seekg(0); // Go to the beginning of the file
                std::string line;
                int currentLine = 0;
                while (std::getline(readLogfile, line)) {
                    if (currentLine == lineNumber) {
                        return line;
                    }
                    currentLine++;
                }
                return ""; // If line not found, return empty string
            }
            return ""; // If file can't be opened, return empty string
        }

        std::vector<std::string> getAllLogs() {
            std::vector<std::string> output;
            std::ifstream readLogfile("/usd/log.txt");
            if (readLogfile.is_open()) {
                readLogfile.clear(); // Clear any EOF flags
                readLogfile.seekg(0); // Go to the beginning of the file
                std::string line;
                while (std::getline(readLogfile, line)) {
                    output.push_back(line);
                }
            }
            return output;
        }

        int getLogLength(){
            std::ifstream readLogfile("/usd/log.txt");
            int lineCount = 0;
            if (readLogfile.is_open()) {
                readLogfile.clear(); // Clear any EOF flags
                readLogfile.seekg(0); // Go to the beginning of the file
                std::string line;
                while (std::getline(readLogfile, line)) {
                    lineCount++;
                }
            }
            return lineCount;
        }

    private:
        std::ofstream logfile;
};