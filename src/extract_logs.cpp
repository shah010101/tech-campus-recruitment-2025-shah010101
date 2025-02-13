#include <iostream>
#include <fstream>
#include <string>

// Windows-specific headers for _mkdir()
#ifdef _WIN32
  #include <direct.h>  // For _mkdir()
  #include <errno.h>
#else
  #include <sys/stat.h>
  #include <sys/types.h>
#endif

/**
 * A naive solution to extract log entries for a given date (YYYY-MM-DD).
 *
 * Compilation (example):
 *     g++ -o extract_logs extract_logs.cpp -O2
 *
 * Usage:
 *     ./extract_logs 2024-12-01
 *
 * Output:
 *     Writes all matching lines to: output/output_2024-12-01.txt
 *
 * Note:
 *   - This solution scans the entire file. For a 1 TB file,
 *     you'd likely need a more sophisticated approach (e.g., indexing or binary search).
 */
int main(int argc, char* argv[])
{
    // -------------------------------------------------------------------------
    // 1. Validate and Parse Command Line Argument
    // -------------------------------------------------------------------------
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <YYYY-MM-DD>\n";
        return 1;
    }
    std::string targetDate = argv[1]; // e.g., "2024-12-01"

    // -------------------------------------------------------------------------
    // 2. Prepare Input and Output
    // -------------------------------------------------------------------------
    // For demonstration, let's assume our log file is "test_logs.txt".
    // Adjust this as needed.
    std::string logFileName = "test_logs.txt";

    std::ifstream logFile(logFileName.c_str());
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open log file: " << logFileName << std::endl;
        return 1;
    }

    // Create the "output" directory if it does not exist.
    // Windows uses _mkdir(), Linux/Unix uses mkdir().
#ifdef _WIN32
    if (_mkdir("output") != 0) {
        // If the directory already exists, errno should be EEXIST, which we can ignore.
        if (errno != EEXIST) {
            std::cerr << "Warning: Could not create 'output' directory. Error code: "
                      << errno << std::endl;
        }
    }
#else
    // On Linux/Unix, we can do mkdir("output", 0755) and ignore if it fails with EEXIST.
    mkdir("output", 0755);
#endif

    // Build the output file path: "output/output_YYYY-MM-DD.txt"
    std::string outputFileName = std::string("output/output_") + targetDate + ".txt";
    std::ofstream outFile(outputFileName.c_str());
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output file: " << outputFileName << std::endl;
        return 1;
    }

    // -------------------------------------------------------------------------
    // 3. Read the File Line by Line and Match the Date
    // -------------------------------------------------------------------------
    // Example log format: "YYYY-MM-DD HH:MM:SS INFO Some message"
    // The date is the first 10 characters: "YYYY-MM-DD"
    const size_t dateLength = targetDate.size(); // Typically 10
    std::string line;

    while (std::getline(logFile, line)) {
        if (line.size() >= dateLength) {
            std::string lineDate = line.substr(0, dateLength);
            if (lineDate == targetDate) {
                outFile << line << "\n";
            }
        }
    }

    // -------------------------------------------------------------------------
    // 4. Cleanup and Exit
    // -------------------------------------------------------------------------
    logFile.close();
    outFile.close();

    std::cout << "Logs for " << targetDate 
              << " have been written to: " << outputFileName << std::endl;
    return 0;
}
