#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;

// --- DATA STRUCTURES ---
struct Range {
    double low;
    double high;
    string type;
};

// Centralized frequency database
// Easily expandable without changing logic
vector<Range> sensorRanges = {
    {40500, 41500, "Microplastic"},
    {41800, 42500, "Microplastic"},
    {43000, 44000, "Microplastic"},
    {35000, 36500, "Non-Microplastic"},
    {37000, 39000, "Non-Microplastic"},
    {39500, 40000, "Non-Microplastic"}
};

// --- LOGIC FUNCTIONS ---

string classifyFrequency(double inputFreq) {
    for (const auto& r : sensorRanges) {
        if (inputFreq >= r.low && inputFreq <= r.high) {
            return r.type;
        }
    }
    return "Unknown Material";
}

// Helper to get current timestamp for the dashboard
string getTimestamp() {
    time_t now = time(0);
    char buf[80];
    struct tm tstruct;
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return string(buf);
}

// --- HTML DASHBOARD GENERATOR ---

void generateHTML(double input, string result, string category) {
    ofstream file("output.html");

    // Dynamic UI Colors based on classification
    string statusColor = "#f7b731"; // Default Yellow
    string resultTextColor = "#ffffff";
    string categoryBg = "#5a5a5a"; // Default Gray

    if (result == "Microplastic") {
        resultTextColor = "#ff4d94"; // High-visibility Pink
        categoryBg = "#1b4332";      // Deep Tech Green
    } else if (result == "Non-Microplastic") {
        resultTextColor = "#00ff88"; // Neon Green
        categoryBg = "#004d4d";      // Dark Teal
    }

    file << "<!DOCTYPE html>\n<html lang='en'>\n<head>\n";
    file << "<meta charset='UTF-8'>\n<meta http-equiv='refresh' content='2'>\n";
    file << "<title>Acoustic Analysis System</title>\n";
    file << "<style>\n";
    file << "  body { font-family: 'Segoe UI', system-ui, sans-serif; background-color: #f4f7f6; margin: 0; padding: 40px; color: #2d3436; }\n";
    file << "  .container { max-width: 1000px; margin: auto; background: white; padding: 40px; border-radius: 20px; box-shadow: 0 15px 35px rgba(0,0,0,0.05); }\n";
    file << "  header { text-align: center; margin-bottom: 50px; }\n";
    file << "  h1 { margin: 0; font-size: 2.2em; color: #1e272e; letter-spacing: -0.5px; border-bottom: 4px solid #00aaff; display: inline-block; }\n";
    file << "  .subtitle { color: #7f8c8d; margin-top: 10px; font-weight: 400; }\n";

    // Grid Layout
    file << "  .grid { display: grid; grid-template-columns: repeat(3, 1fr); gap: 25px; margin-bottom: 50px; }\n";
    file << "  .card { padding: 30px 20px; border-radius: 15px; color: white; text-align: center; transition: 0.3s; }\n";
    file << "  .card:hover { transform: translateY(-5px); }\n";
    file << "  .card-label { font-size: 0.85em; text-transform: uppercase; letter-spacing: 1.5px; margin-bottom: 15px; opacity: 0.8; }\n";
    file << "  .card-value { font-size: 1.7em; font-weight: 700; }\n";

    // Card Themes
    file << "  .bg-primary { background: linear-gradient(135deg, #485e75, #2c3e50); }\n"; // Detected Freq
    file << "  .bg-secondary { background: linear-gradient(135deg, #1e272e, #000000); }\n"; // Classification
    file << "  .bg-accent { background: " << categoryBg << "; }\n"; // Category

    // Info Section
    file << "  .info-section { border-top: 1px solid #edf2f7; padding-top: 40px; display: grid; grid-template-columns: 2fr 1fr; gap: 40px; }\n";
    file << "  table { width: 100%; border-collapse: collapse; }\n";
    file << "  th { text-align: left; color: #a0aec0; font-size: 0.8em; text-transform: uppercase; padding: 12px; }\n";
    file << "  td { padding: 15px 12px; border-bottom: 1px solid #f7fafc; font-size: 0.95em; }\n";
    file << "  .status-tag { padding: 4px 10px; border-radius: 20px; font-size: 0.8em; font-weight: bold; background: #e2e8f0; }\n";
    file << "  .footer { text-align: center; margin-top: 50px; color: #cbd5e0; font-size: 0.85em; }\n";
    file << "</style>\n</head>\n<body>\n";

    file << "<div class='container'>\n";
    file << "  <header>\n";
    file << "    <h1>Acoustic Frequency Analysis</h1>\n";
    file << "    <div class='subtitle'>Material Identification & Classification Interface</div>\n";
    file << "  </header>\n";

    // Dashboard Cards
    file << "  <div class='grid'>\n";
    file << "    <div class='card bg-primary'><div class='card-label'>Detected Frequency</div><div class='card-value' style='color:#f7b731;'>" << fixed << setprecision(2) << input << " Hz</div></div>\n";
    file << "    <div class='card bg-secondary'><div class='card-label'>Classification Result</div><div class='card-value' style='color:" << resultTextColor << ";'>" << result << "</div></div>\n";
    file << "    <div class='card bg-accent'><div class='card-label'>Storage Category</div><div class='card-value'>" << category << "</div></div>\n";
    file << "  </div>\n";

    // Detailed Data Table
    file << "  <div class='info-section'>\n";
    file << "    <div>\n";
    file << "      <h3 style='margin-top:0;'>Reference Frequency Spectrums</h3>\n";
    file << "      <table>\n";
    file << "        <tr><th>Acoustic Range</th><th>Target Material</th><th>System Status</th></tr>\n";
    file << "        <tr><td>40.5 kHz - 44.0 kHz</td><td>Microplastics (PET/PE)</td><td><span class='status-tag' style='color:#2d6a4f;'>ACTIVE</span></td></tr>\n";
    file << "        <tr><td>35.0 kHz - 40.0 kHz</td><td>Organic / Non-Plastic</td><td><span class='status-tag' style='color:#2d6a4f;'>ACTIVE</span></td></tr>\n";
    file << "        <tr><td>Undefined</td><td>Noise / Unknown</td><td><span class='status-tag'>MONITORING</span></td></tr>\n";
    file << "      </table>\n";
    file << "    </div>\n";

    // Visual Circle Indicator
    file << "    <div style='text-align:center;'>\n";
    file << "       <div style='width:120px; height:120px; border: 12px solid #edf2f7; border-top-color: #00aaff; border-radius: 50%; margin:auto; display:flex; align-items:center; justify-content:center; animation: spin 2s linear infinite;'>\n";
    file << "         <span style='font-weight:bold; color:#2c3e50;'>RUNNING</span>\n";
    file << "       </div>\n";
    file << "    </div>\n";
    file << "  </div>\n";

    file << "  <div class='footer'>System Clock: " << getTimestamp() << " | Data Analysis Engine v2.4</div>\n";
    file << "</div>\n";

    file << "</body>\n</html>";
    file.close();
}

// --- MAIN PROGRAM ---

int main() {
    double freqInput;

    cout << "============================================" << endl;
    cout << "   ACOUSTIC MATERIAL CLASSIFICATION v2.0   " << endl;
    cout << "============================================" << endl;

    while (true) {
        cout << "\nEnter detected frequency in Hz (or 0 to exit): ";
        if (!(cin >> freqInput)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (freqInput == 0) break;

        // 1. Logic Processing
        string result = classifyFrequency(freqInput);
        string category;

        if (result == "Microplastic") {
            category = "PLASTIC BIN";
        } else if (result == "Non-Microplastic") {
            category = "GENERAL BIN";
        } else {
            category = "MANUAL REVIEW";
        }

        // 2. Terminal Output
        cout << ">> Result: [" << result << "] -> Action: Route to " << category << endl;

        // 3. HTML Dashboard Update
        generateHTML(freqInput, result, category);
        cout << ">> Dashboard updated. View 'output.html' to see results." << endl;
    }

    return 0;
}
