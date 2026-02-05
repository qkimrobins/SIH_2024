#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
// Microplastic frequency ranges (in Hz)
struct Range {
    double low;
    double high;
};
Range microRanges[] = {
    {40500, 41500},
    {41800, 42500},
    {43000, 44000}
};
int microRangeCount = 3;

// Non-microplastic ranges
Range nonMicroRanges[] = {
    {35000, 36500},
    {37000, 39000},
    {39500, 40000}
};
int nonMicroRangeCount = 3;
// Check which range the input belongs to
bool inRange(double value, Range r) {
    return (value >= r.low && value <= r.high);
}
string classifyFrequency(double inputFreq) {
    for (int i = 0; i < microRangeCount; i++) {
        if (inRange(inputFreq, microRanges[i])) {
            return "Microplastic";
        }
    }
    // Check if inside any non-microplastic range
    for (int i = 0; i < nonMicroRangeCount; i++) {
        if (inRange(inputFreq, nonMicroRanges[i])) {
            return "Non-Microplastic";
        }
    }
    return "Unknown Material";
}
// HTML Output Generator
void generateHTML(double input, string result, string category) {
    ofstream file("output.html");
    stringstream ss_input;
    ss_input << input;
    string input_str = ss_input.str();

    // Start of HTML
    file << "<!DOCTYPE html>\n<html>\n<head>\n";
    file << "<title>Frequency Detection Output</title>\n";
    file << "<meta http-equiv=\"refresh\" content=\"1\">\n";
    file << "<style>\n";
    file << "/* --- STYLING FOR A MODERN, TECHY, SUBTLE LOOK --- */\n";
    file << "body { \n";
    file << "    /* Dark background with a slight gradient for depth */\n";
    file << "    background: #1e2025; \n";
    file << "    color: #e0e0e0; /* Off-white for general readability */\n";
    file << "    font-family: 'Segoe UI', 'Roboto', 'Helvetica Neue', sans-serif; /* Modern, clean sans-serif font */\n";
    file << "    padding: 40px; \n";
    file << "    margin: 0;\n";
    file << "    display: flex;\n";
    file << "    justify-content: center;\n";
    file << "    align-items: center;\n";
    file << "    min-height: 100vh;\n";
    file << "}\n\n";

    file << ".box { \n";
    file << "    /* Main data container - dark and minimal */\n";
    file << "    background: #2b2e34; /* Slightly lighter dark background */\n";
    file << "    padding: 30px; \n";
    file << "    border-radius: 8px; /* Clean, modern corner radius */\n";
    file << "    /* Subtle, dark box shadow for depth, no bright glow */\n";
    file << "    box-shadow: 0 4px 15px rgba(0, 0, 0, 0.4); \n";
    file << "    width: 100%;\n";
    file << "    max-width: 450px;\n";
    file << "    transition: transform 0.3s ease;\n";
    file << "    border-top: 3px solid #00aaff; /* A thin, bright accent line */\n";
    file << "}\n\n";

    file << ".box:hover {\n";
    file << "    /* Subtle hover effect */\n";
    file << "    transform: translateY(-2px);\n";
    file << "}\n\n";

    file << "h2 { \n";
    file << "    /* Main heading style */\n";
    file << "    color: #00aaff; /* Primary tech blue */\n";
    file << "    text-align: left;\n";
    file << "    border-bottom: 1px solid #3a3e46; /* Thin, dark separator */\n";
    file << "    padding-bottom: 15px;\n";
    file << "    margin-top: 0;\n";
    file << "    margin-bottom: 20px;\n";
    file << "    font-weight: 500; /* Medium weight for professionalism */\n";
    file << "    font-size: 1.6em;\n";
    file << "}\n\n";

    file << "p {\n";
    file << "    /* General paragraph styling - use flexbox for aligned label and value */\n";
    file << "    margin: 18px 0;\n";
    file << "    padding: 0;\n";
    file << "    font-size: 1em;\n";
    file << "    display: flex; \n";
    file << "    justify-content: space-between;\n";
    file << "}\n\n";

    file << "p strong {\n";
    file << "    /* Highlighted labels */\n";
    file << "    color: #99aab5; /* Subdued color for labels */\n";
    file << "    font-weight: normal;\n";
    file << "    text-transform: uppercase;\n";
    file << "    font-size: 0.9em;\n";
    file << "    letter-spacing: 0.5px;\n";
    file << "}\n\n";

    file << "/* Specific styling for the data values */\n";
    file << "p span {\n";
    file << "    font-family: 'Roboto Mono', monospace; /* Monospace for data values */\n";
    file << "    font-weight: bold;\n";
    file << "}\n\n";

    file << "p:nth-of-type(1) span { /* User Frequency Input */\n";
    file << "    color: #f7b731; /* Amber/Yellow for input data */\n";
    file << "}\n\n";

    file << "p:nth-of-type(2) span { /* Classification Result */\n";
    file << "    color: #e55959; /* Soft Red for the main result */\n";
    file << "    font-size: 1.1em;\n";
    file << "}\n\n";

    file << "p:nth-of-type(3) span { /* Category */\n";
    file << "    color: #00aaff; /* Primary blue for the final category */\n";
    file << "    font-size: 1.1em;\n";
    file << "}\n\n";

    file << "/* Add a separator line between data points */\n";
    file << "p + p {\n";
    file << "    border-top: 1px dashed #3a3e46;\n";
    file << "    padding-top: 15px;\n";
    file << "}\n";

    file << "</style>\n";
    file << "</head>\n<body>\n";

    file << "<div class='box'>\n";
    file << "<h2>Real-Time Acoustic Frequency Classification</h2>\n";
    file << "<p><strong>User Frequency Input</strong> <span>" << input_str << " Hz</span></p>\n";
    file << "<p><strong>Classification Result</strong> <span>" << result << "</span></p>\n";
    file << "<p><strong>Category</strong> <span>" << category << "</span></p>\n";
    file << "</div>\n";

    file << "</body>\n</html>";
    file.close();
}
// MAIN PROGRAM
int main() {
    double freqInput;
    cout << "\n=== MICROPLASTIC ACOUSTIC RANGE DETECTION ===\n";
    cout << "Enter detected frequency (in Hz): ";
    // Example test input: 42000 (Microplastic), 38000 (Non-Microplastic), 50000 (Unknown)
    cin >> freqInput;
    // Classification
    string result = classifyFrequency(freqInput);
    string category;
    if (result == "Microplastic") category = "MICROPLASTIC BIN";
    else if (result == "Non-Microplastic") category = "NON-MICROPLASTIC BIN";
    else category = "UNIDENTIFIED / NEEDS FURTHER ANALYSIS";
    cout << "\n--- RESULT ---\n";
    cout << "Input Frequency: " << freqInput << " Hz\n";
    cout << "Classification: " << result << "\n";
    cout << "Category: " << category << "\n";
    generateHTML(freqInput, result, category);
    cout << "\nOutput written to 'output.html'. Open it in a browser.\n";
    return 0;
}
