#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
#include<bits/stdc++.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <limits> // for numeric_limits
#include <thread>
#include <string>
#include <iomanip> // for std::setw
#include <ctime>   // for time-related functions
#include <windows.h>
#include <chrono>
#ifdef _WIN32
#include<windows.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#endif
using namespace std;

struct Task {
    string time;
    string description;
};
vector<Task> tasks;

struct StudySession {
    string subject;
    string startTime;
    string endTime;
};
enum TimetableCategory {
    BUS_SCHEDULE,
    CLASS_ROUTINE,
    OTHER_ACTIVITY
};
struct TimetableEntry {
    string time;
    string description;
    string day;
    tm dateTime;
    TimetableCategory category;
    string subjectName;    // For class routine
    string teacherName;
};
struct Reminder {
    string message;
    tm reminderTime;
};
struct Note {
    string timestamp; // Optional timestamp for the note
    string content;
};
struct HealthEntry
{
    string date;
    string category;
    string details;
};
struct HealthMetric
{
    string date;
    string metricName;
    double value;
};
struct MealEntry
{
    string time;
    string mealName;
};
struct BusinessIdea {
    string details;
};
struct Investment {
    string name;
    double amount;
};
struct Contact {
    string name;
    string company;
    string position;
};
struct NetworkingEvent {
        string eventName;
        string eventDescription;
};
struct Diet {
    string planName;
    string description;
};
struct Exercise {
    string planName;
    string description;
};
struct Reminder2 {
    tm time;
    string description;
};

// Global vectors to store data
vector<BusinessIdea> businessIdeas;
vector<Investment> investments;
vector<Contact> contacts;
unordered_map<string, string> users; // Stores usernames and passwords
unordered_map<string, vector<MealEntry>> mealTimetables; // Stores user meal timetables
unordered_map<string, vector<string>> jobSearchResults;
unordered_map<string, vector<string>> appliedJobs;
unordered_map<string, vector<string>> scheduledInterviews;
vector<NetworkingEvent> networkingEvents; // Example storage for networking events
vector<Diet> dietPlans; // Example storage for diet plans
vector<Exercise> exercisePlans;
vector<HealthEntry> healthEntries;// Vectors to store Health Entries and Metrics
vector<HealthMetric> healthMetrics;
unordered_map<string, vector<TimetableEntry>> timetables; // Stores user class timetables
unordered_map<string, vector<Reminder>> reminders; // Stores user reminders
unordered_map<string, vector<Note>> userNotes; // Map to store user notes
unordered_map<string, vector<StudySession>> studySchedules;

//void showUserRoleMenu();
// Function to show the user role menu
void addTask();
void viewTasks();
void remindToDrinkWater();
void homemakerMenu();
void showUserRoleMenu(const string &username);
void showAcademicTimetable(const string &username);
void addBusSchedule(vector<TimetableEntry>& busSchedules);
void addClassRoutine(vector<TimetableEntry>& classRoutine);
void addOtherActivity(vector<TimetableEntry>& otherActivities);
void addAcademicTimetable(const string &username);
void showStudentPanel(const std::string& studentName);
bool parseDateTime();
void clearUserData(const string& username);
void showNotes(const string& username);
void addNote(const string& username);
void printCentered();
void clearConsole();
void timeshow();
void addStudySession(const string& username);
void showStudySchedule(const string& username);
void healthMenu();
void printBox(const string& message);
void setReminder(const string& username);
void showReminders(const string& username);
void checkReminders(const string& username);
int getConsoleWidth();
void handleAthleteMenu();
void handleTrainingSchedule();
void handlePerformanceTracking();
void handleNutritionPlanning();
void retireeMenu();
void handleHealthTracking();
void recordHealthMetric();
void addHealthEntry();
void viewHealthEntries();
void editHealthEntry();
void deleteHealthEntry();
void viewHealthMetrics();
void showEmploymentPanel();
void searchForJobs();
void showJobSearchResults();
void applyForJob();
void showOtherOptions();
void addNetworkingEvent();
void viewNetworkingEvents();
void showAppliedJobs();
void scheduleInterview();
void showScheduledInterviews();
void handleWorkRelatedHealth();
void showHealthOptions();
void handleDietPlan();
void handleExercisePlan();
void handleEntrepreneurMenu();
void handleBusinessIdeas();
void handleInvestments();
void handleNetworking();
void handleMiscellaneous();
void showStudentPanel(const string &username);

int getConsoleWidth()
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
#endif
}

void printCentered(string message, bool animated = false)
{
    int consoleWidth = getConsoleWidth();
    int messageLength = message.length();
    int paddingLeft = (consoleWidth - messageLength) / 2;

    if (paddingLeft > 0)
    {
        if (animated)
        {
            for (int i = 0; i < paddingLeft; ++i)
            {
                cout << " ";
                this_thread::sleep_for(chrono::milliseconds(10)); // Animation delay
            }
            for (char c : message)
            {
                cout << c << flush;
                this_thread::sleep_for(chrono::milliseconds(30)); // Animation delay
            }
            cout << endl;
        }
        else
        {
            cout << string(paddingLeft, ' ') << message << endl;
        }
    }
    else
    {
        cout << message << endl;
    }
}

void printBox(const string& message)
{
    int width = message.length() + 4; // Account for padding and borders
    string topBottomBorder(width, '=');

    // Print top border
    cout << "+" << topBottomBorder << "+" << endl;

    // Print message with left and right borders
    cout << "| " << message << " |" << endl;

    // Print bottom border
    cout << "+" << topBottomBorder << "+" << endl;
}

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void animateText(const string& text)
{
    for (char c : text)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(30)); // Animation delay
    }
}

void timeshow()
{
    // Get current time
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    // Format current time
    char currTime[9];
    strftime(currTime, sizeof(currTime), "%H:%M:%S", localTime);

    // Format current date
    char currDate[11];
    strftime(currDate, sizeof(currDate), "%d-%m-%Y", localTime);

    // Format current day
    char currDay[20];
    strftime(currDay, sizeof(currDay), "%A", localTime);

    printBox(string(currTime) + " " + string(currDate) + " " + string(currDay));
}

void showWelcomePanel()
{
    clearConsole();
    string appName = "TimeWise24";
    string welcomeLine = "Welcome to our project";
    string createdBy = "Created By";
    string creatorName = "Nusrat Afrra Tanisha";
    string submittedTo = "Submitted to";
    string lecturerInfo = "Nuren Nafisa, Lecturer, Dept of CSE, IIUC";
    cout << endl << endl << endl;

    // Display the main welcome message and app name with animation
    printCentered("===================================");
    animateText("                                                 Welcome to our project");
    cout << endl;
    animateText("                                                      TimeWise24");
    cout << endl;
    animateText("                                              Lets utilize your time here");
    cout << endl;
    printCentered("===================================");
    cout << endl << endl;

    // Display "Created By" and creator's name with animation
    printCentered(createdBy);
    printCentered("====================");
    printCentered(creatorName);
    cout << endl << endl;

    // Display "Submitted to" and lecturer info with animation
    printCentered(submittedTo);
    printCentered("=================");
    printCentered(lecturerInfo);
    cout << endl << endl;

    // Display the continue message at the bottom with animation
    animateText("                            ===================================================================");
    cout << endl;
    animateText("                                              PRESS ENTER TO CONTINUE..........");

    // Wait for user to press Enter
    while (cin.get() != '\n') {}  // Wait until Enter is pressed

    // Clear any remaining characters in the input buffer
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void showSignUpPanel() {
    clearConsole();
    string username, password;

    printCentered("======================");
    printCentered("     Sign Up Panel    ");
    printCentered("======================");

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // Save the new user
    users[username] = password;

    printCentered("Sign up successful!");
    printCentered("Press Enter to return to the main menu...");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
// Updated showLoginPanel function to call showUserRoleMenu after successful login
bool showLoginPanel(string& loggedInUser)
{
    clearConsole();
    string username, password;

    printCentered("======================");
    printCentered("      Login Panel     ");
    printCentered("======================");

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // Validate the username and password
    if (users.find(username) != users.end() && users[username] == password)
    {
        loggedInUser = username;
        printCentered("Login successful!");
        printCentered("Press Enter to continue...");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        // Show the user role menu after successful login
        showUserRoleMenu(loggedInUser);
        return true;
    }
    else
    {
        printCentered("Login failed. Please try again.");
        printCentered("Press Enter to return to the main menu...");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return false;
    }
}
// Function to show the user role menu
void showStudentPanel(const string &username) {
    bool isRunning = true;

    while (isRunning) {
        clearConsole();
        timeshow();
        cout << endl << endl << endl << endl << endl << endl;
        printCentered("Student Panel");
        printCentered("=============================================");

        printCentered("1. Academic Timetable");
        printCentered("2. Show Academic Timetable");
        printCentered("3. Set a Home study schedule");
        printCentered("4. Show Home study schedule");
        printCentered("5. Schedule a reminder");
        printCentered("6. Show Schedule a reminder");
        printCentered("7. Take a note");
        printCentered("8. Show Note");
        printCentered("9. Other");
        printCentered("10. Erase Everything");
        printCentered("11. Exit");
        printCentered("=============================================");

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
            case 1: {
                addAcademicTimetable(username);
                break;
            }
            case 2: {
                showAcademicTimetable(username);
                break;
            }
            case 3: {
                // Function to Set a Home study schedule
                addStudySession(username);
                break;
            }
            case 4: {
                // Function to Show Home study schedule"
                showStudySchedule(username);
                break;
            }
            case 5: {
                // Function to Schedule a reminder
                setReminder(username);
                break;
            }
            case 6: {
                // Function show Schedule a reminder
                showReminders(username);
                break;
            }
            case 7: {
                // Function to take a note
                  addNote(username);
                break;
            }
            case 8: {
                // Function to show note
                showNotes(username);
                break;
            }
            case 9: {
                int otherChoice;
                clearConsole();
                timeshow();
                printCentered("Other Options");
                printCentered("=============================================");
                printCentered("1. Health");
                printCentered("2. Extra Activity");
                printCentered("3. Back to Student Panel");
                printCentered("=============================================");
                cout << "Enter your choice: ";
                cin >> otherChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

                switch (otherChoice) {
                    case 1: {
                        // Function to handle health options
                        healthMenu();
                        break;
                    }
                    case 2: {
                        // Function to handle extra activity options
                        break;
                    }
                    case 3: {
                        // Return to student panel
                        break;
                    }
                    default: {
                        printCentered("Invalid choice. Please try again.");
                        break;
                    }
                }
                break;
            }
            case 10: {
                // Function to erase everything
                clearUserData(username);
                break;
            }
            case 11: {
                isRunning = false;
                break;
            }
            default: {
                printCentered("Invalid choice. Please try again.");
                break;
            }
        }
        // Check reminders each loop iteration
        checkReminders(username);
    }
    printCentered("Exiting Student Panel...");
    // Optionally, add any cleanup or additional messages here
}
void showEmploymentPanel() {
    bool isRunning = true;

    while (isRunning) {
        clearConsole();
        timeshow();
        cout << endl << endl << endl << endl << endl << endl;
        printCentered("Employment Panel");
        printCentered("=============================================");
        printCentered("1. Apply for a Job");
        printCentered("2. View Applied Jobs");
        printCentered("3. Schedule an Interview");
        printCentered("4. Show Scheduled Interviews");
        printCentered("5. Other");
        printCentered("6. Back");
        printCentered("=============================================");

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
            case 1:
                searchForJobs();
                showJobSearchResults();
                applyForJob();
                break;
            case 2:
                showAppliedJobs();
                break;
            case 3:
                scheduleInterview();
                break;
            case 4:
                showScheduledInterviews();
                break;
            case 5:
                showOtherOptions();
                break;
            case 6:
                isRunning = false;
                break;
            default:
                printCentered("Invalid choice. Please try again.");
                break;
        }

        if (isRunning) {
            printCentered("Press Enter to continue...");
            cin.get();
        }
    }
}

void searchForJobs() {
    clearConsole();
    printCentered("Searching for jobs...");

    // Simulate job search results
    vector<string> jobs = {
        "Software Engineer at ABC Corp",
        "Data Analyst at XYZ Inc",
        "Project Manager at LMN Ltd",
        "Systems Administrator at OPQ Co",
        "Business Analyst at RST LLC"
    };
    string username = "test_user"; // This should be the actual logged-in user
    jobSearchResults[username] = jobs;

    printCentered("Search completed.");
}

void showJobSearchResults() {
    clearConsole();
    printCentered("Search Results:");

    string username = "test_user"; // This should be the actual logged-in user
    printCentered("=============================================");
    if (jobSearchResults.find(username) != jobSearchResults.end()) {
        for (const string& job : jobSearchResults[username]) {
            printCentered(job);
        }
    } else {
        printCentered("No job search results found.");
    }
    printCentered("=============================================");
    printCentered("Press Enter to continue...");
    cin.get();
}

void applyForJob() {
    clearConsole();
    printCentered("Applying for a job...");
    printCentered("=============================================");
    string username = "test_user"; // This should be the actual logged-in user
    if (jobSearchResults.find(username) != jobSearchResults.end()) {
        for (size_t i = 0; i < jobSearchResults[username].size(); ++i) {
            cout << i + 1 << ". " << jobSearchResults[username][i] << endl;
        }

        int choice;
        cout << "Choose a job you want to apply for: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        if (choice > 0 && choice <= jobSearchResults[username].size()) {
            appliedJobs[username].push_back(jobSearchResults[username][choice - 1]);
            printCentered("Application submitted.");
        } else {
            printCentered("Invalid choice. No job applied.");
        }
    } else {
        printCentered("No job search results found.");
    }

    printCentered("Press Enter to continue...");
    cin.get();
}

void showAppliedJobs() {
    clearConsole();
    printCentered("Applied Jobs:");
    printCentered("=============================================");
    cout << endl << endl << endl << endl;
    string username = "test_user"; // This should be the actual logged-in user
    if (appliedJobs.find(username) != appliedJobs.end() && !appliedJobs[username].empty()) {
        for (const string& job : appliedJobs[username]) {
            printCentered(job);
        }
    } else {
        printCentered("No applied jobs found.");
    }
    cout << endl << endl << endl << endl;
    printCentered("=============================================");
    printCentered("Press Enter to continue...");
    cin.get();
}

void scheduleInterview() {
    clearConsole();
    printCentered("Scheduling an interview...");

    string username = "test_user"; // This should be the actual logged-in user
    if (appliedJobs.find(username) != appliedJobs.end()) {
        for (size_t i = 0; i < appliedJobs[username].size(); ++i) {
            cout << i + 1 << ". " << appliedJobs[username][i] << endl;
        }

        int choice;
        cout << "Enter the job number to schedule an interview for: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        printCentered("=============================================");
        if (choice > 0 && choice <= appliedJobs[username].size()) {
            string interviewTime;
            cout << "Enter the interview time: ";
            getline(cin, interviewTime);
            // Simulate scheduling time
            this_thread::sleep_for(chrono::seconds(2)); // Simulate scheduling time of 2 seconds

            // Store the scheduled interview with time
            string scheduledInterview = appliedJobs[username][choice - 1] + " at " + interviewTime;
            scheduledInterviews[username].push_back(scheduledInterview);
            cout << endl << endl << endl << endl << endl;
            printCentered("Interview scheduled.");
        } else {
            printCentered("Invalid choice. No interview scheduled.");
        }
    } else {
        printCentered("No applied jobs found.");
    }
    printCentered("=============================================");
    printCentered("Press Enter to continue...");
    cin.get();
}
void showScheduledInterviews() {
    clearConsole();
    printCentered("Scheduled Interviews:");
    printCentered("=============================================");
    string username = "test_user"; // This should be the actual logged-in user
    if (scheduledInterviews.find(username) != scheduledInterviews.end() && !scheduledInterviews[username].empty()) {
        for (const string& interview : scheduledInterviews[username]) {
            // Split the interview string to separate job and time
            size_t pos = interview.find(" at ");
            if (pos != string::npos && pos + 4 < interview.length()) {
                string job = interview.substr(0, pos);
                string time = interview.substr(pos + 4);

                // Print the job and scheduled time
                cout << endl << endl << endl << endl << endl;
                printCentered(job);
                printCentered("Scheduled at " + time);
            }
        }
    } else {
        cout << endl << endl << endl << endl << endl;
        printCentered("No scheduled interviews found.");
    }
    cout << endl << endl << endl << endl << endl;
    printCentered("=============================================");
    printCentered("Press Enter to continue...");
    cin.get();
}
void showOtherOptions() {
    bool otherRunning = true;
    while (otherRunning) {
        clearConsole();
        timeshow();
        printCentered("Other Options");
        printCentered("=============================================");
        printCentered("1. Health");
        printCentered("2. Networking Events");
        printCentered("3. Back");
        printCentered("=============================================");
        cout << "Enter your choice: ";
        int otherChoice;
        cin >> otherChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (otherChoice) {
            case 1:
                showHealthOptions();
                break;
            case 2:
                handleNetworking();
                break;
            case 3:
                otherRunning = false;
                break;
            default:
                printCentered("Invalid choice. Please try again.");
                break;
        }

        if (otherRunning) {
            printCentered("Press Enter to continue...");
            cin.get();
        }
    }
}
void showHealthOptions() {
    bool healthRunning = true;
    while (healthRunning) {
        clearConsole();
        timeshow();
        printCentered("Health Options");
        printCentered("=============================================");
        printCentered("1. Diet Plan");
        printCentered("2. Exercise Plan");
        printCentered("3. Back");
        printCentered("=============================================");
        cout << "Enter your choice: ";
        int healthChoice;
        cin >> healthChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (healthChoice) {
            case 1:
                handleDietPlan();
                break;
            case 2:
                handleExercisePlan();
                break;
            case 3:
                healthRunning = false;
                break;
            default:
                printCentered("Invalid choice. Please try again.");
                break;
        }

        if (healthRunning) {
            printCentered("Press Enter to continue...");
            cin.get();
        }
    }
}
void handleDietPlan() {
    clearConsole();
    timeshow();
    printCentered("Diet Plan Options");
    printCentered("=================");

    // Example pre-defined diet plans
    vector<Diet> dietPlans = {
        {"Low Carb Diet", "Focuses on reducing carbohydrate intake."},
        {"Mediterranean Diet", "Emphasizes fruits, vegetables, whole grains, and olive oil."},
        {"Keto Diet", "High-fat, adequate-protein, low-carbohydrate diet."},
    };

    int choice;
    int chosenDietIndex = -1; // Initialize chosenDietIndex here

    do {
        clearConsole();
        timeshow();
        printCentered("Diet Plan Options");
        printCentered("=================");
        printCentered("1. Choose a Diet Plan");
        printCentered("2. View Chosen Diet Plan");
        printCentered("3. Edit Chosen Diet Plan");
        printCentered("4. Delete Chosen Diet Plan");
        printCentered("5. Back to Main Menu");
        printCentered("=================");

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
            case 1: {
                clearConsole();
                timeshow();
                printCentered("Choose a Diet Plan");
                printCentered("=================");
                for (size_t i = 0; i < dietPlans.size(); ++i) {
                    printCentered(to_string(i + 1) + ". " + dietPlans[i].planName);
                }
                cout << "Enter your choice (1-" << dietPlans.size() << "): ";
                int planChoice;
                cin >> planChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (planChoice >= 1 && planChoice <= dietPlans.size()) {
                    chosenDietIndex = planChoice - 1; // Store the chosen diet plan index
                    printCentered("Diet plan chosen: " + dietPlans[chosenDietIndex].planName);
                } else {
                    printCentered("Invalid choice. Please try again.");
                }
                break;
            }
            case 2: {
                if (chosenDietIndex == -1) {
                    printCentered("No diet plan chosen yet.");
                } else {
                    printCentered("Chosen Diet Plan:");
                    // Display the chosen diet plan
                    printCentered("- Name: " + dietPlans[chosenDietIndex].planName);
                    printCentered("- Description: " + dietPlans[chosenDietIndex].description);
                }
                break;
            }
            case 3: {
                if (chosenDietIndex == -1) {
                    printCentered("No diet plan chosen yet.");
                } else {
                    clearConsole();
                    timeshow();
                    printCentered("Choose a Diet Plan to Edit");
                    printCentered("=================");
                    for (size_t i = 0; i < dietPlans.size(); ++i) {
                        printCentered(to_string(i + 1) + ". " + dietPlans[i].planName);
                    }
                    cout << "Enter your choice (1-" << dietPlans.size() << "): ";
                    int editChoice;
                    cin >> editChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                    if (editChoice >= 1 && editChoice <= dietPlans.size()) {
                        chosenDietIndex = editChoice - 1; // Update chosen diet plan index
                        printCentered("Editing Diet plan: " + dietPlans[chosenDietIndex].planName);
                        // Display current details
                        printCentered("- Name: " + dietPlans[chosenDietIndex].planName);
                        printCentered("- Description: " + dietPlans[chosenDietIndex].description);
                        // Prompt for new name and description (simulated)
                        cout << "Enter new diet plan name: ";
                        string newPlanName;
                        getline(cin, newPlanName);
                        dietPlans[chosenDietIndex].planName = newPlanName;
                        cout << "Enter new diet plan description: ";
                        string newDescription;
                        getline(cin, newDescription);
                        dietPlans[chosenDietIndex].description = newDescription;
                        printCentered("Diet plan updated!");
                    } else {
                        printCentered("Invalid choice. Please try again.");
                    }
                }
                break;
            }
            case 4: {
                if (chosenDietIndex == -1) {
                    printCentered("No diet plan chosen yet.");
                } else {
                    printCentered("Deleting Chosen Diet Plan:");
                    // Display details of the chosen diet plan
                    printCentered("- Name: " + dietPlans[chosenDietIndex].planName);
                    printCentered("- Description: " + dietPlans[chosenDietIndex].description);
                    // Confirm deletion
                    char confirm;
                    cout << "Are you sure you want to delete this diet plan? (y/n): ";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') {
                        chosenDietIndex = -1; // Reset chosen index after deletion
                        printCentered("Diet plan deleted!");
                    } else {
                        printCentered("Deletion canceled.");
                    }
                }
                break;
            }
            case 5: {
                return; // Return to main menu
            }
            default: {
                printCentered("Invalid choice. Please try again.");
                break;
            }
        }

        printCentered("Press Enter to continue...");
        cin.get();
    } while (true);
}
void handleExercisePlan() {
    clearConsole();
    timeshow();
    printCentered("Exercise Plan Options");
    printCentered("====================");

    // Fixed set of exercise plans
    vector<Exercise> exercisePlans = {
        {"Cardio Workout", "Focuses on cardiovascular exercises like running, cycling, etc."},
        {"Strength Training", "Involves resistance exercises to build muscle strength."},
        {"Yoga Routine", "Combines physical postures, breathing exercises, and meditation."},
        {"HIIT Workout", "High-intensity interval training for quick and effective workouts."},
    };

    int choice;
    int chosenExerciseIndex = -1; // Initialize chosenExerciseIndex here

    do {
        clearConsole();
        timeshow();
        printCentered("Exercise Plan Options");
        printCentered("====================");
        printCentered("1. Choose an Exercise Plan");
        printCentered("2. View Chosen Exercise Plan");
        printCentered("3. Edit Chosen Exercise Plan");
        printCentered("4. Delete Chosen Exercise Plan");
        printCentered("5. Back to Main Menu");
        printCentered("====================");

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
            case 1: {
                clearConsole();
                timeshow();
                printCentered("Choose an Exercise Plan");
                printCentered("====================");
                for (size_t i = 0; i < exercisePlans.size(); ++i) {
                    printCentered(to_string(i + 1) + ". " + exercisePlans[i].planName);
                }
                cout << "Enter your choice (1-" << exercisePlans.size() << "): ";
                int planChoice;
                cin >> planChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (planChoice >= 1 && planChoice <= exercisePlans.size()) {
                    chosenExerciseIndex = planChoice - 1; // Store the chosen exercise plan index
                    printCentered("Exercise plan chosen: " + exercisePlans[chosenExerciseIndex].planName);
                } else {
                    printCentered("Invalid choice. Please try again.");
                }
                break;
            }
            case 2: {
                if (chosenExerciseIndex == -1) {
                    printCentered("No exercise plan chosen yet.");
                } else {
                    printCentered("Chosen Exercise Plan:");
                    // Display the chosen exercise plan
                    printCentered("- Name: " + exercisePlans[chosenExerciseIndex].planName);
                    printCentered("- Description: " + exercisePlans[chosenExerciseIndex].description);
                }
                break;
            }
            case 3: {
                if (chosenExerciseIndex == -1) {
                    printCentered("No exercise plan chosen yet.");
                } else {
                    clearConsole();
                    timeshow();
                    printCentered("Choose an Exercise Plan to Edit");
                    printCentered("====================");
                    for (size_t i = 0; i < exercisePlans.size(); ++i) {
                        printCentered(to_string(i + 1) + ". " + exercisePlans[i].planName);
                    }
                    cout << "Enter your choice (1-" << exercisePlans.size() << "): ";
                    int editChoice;
                    cin >> editChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                    if (editChoice >= 1 && editChoice <= exercisePlans.size()) {
                        chosenExerciseIndex = editChoice - 1; // Update chosen exercise plan index
                        printCentered("Editing Exercise plan: " + exercisePlans[chosenExerciseIndex].planName);
                        // Display current details
                        printCentered("- Name: " + exercisePlans[chosenExerciseIndex].planName);
                        printCentered("- Description: " + exercisePlans[chosenExerciseIndex].description);
                        // No prompts for editing name and description as per your requirement
                        printCentered("Exercise plan updated!");
                    } else {
                        printCentered("Invalid choice. Please try again.");
                    }
                }
                break;
            }
            case 4: {
                if (chosenExerciseIndex == -1) {
                    printCentered("No exercise plan chosen yet.");
                } else {
                    printCentered("Delete Chosen Exercise Plan:");
                    // Display details of the chosen exercise plan
                    printCentered("- Name: " + exercisePlans[chosenExerciseIndex].planName);
                    printCentered("- Description: " + exercisePlans[chosenExerciseIndex].description);
                    // Confirm deletion
                    char confirm;
                    cout << "Are you sure you want to delete this exercise plan? (y/n): ";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') {
                        chosenExerciseIndex = -1; // Reset chosen index after deletion
                        printCentered("Exercise plan deleted!");
                    } else {
                        printCentered("Deletion canceled.");
                    }
                }
                break;
            }
            case 5: {
                return; // Return to main menu
            }
            default: {
                printCentered("Invalid choice. Please try again.");
                break;
            }
        }

        printCentered("Press Enter to continue...");
        cin.get();
    } while (true);
}

void showUserRoleMenu(const string &username)
{
    bool isRoleMenuRunning = true;
    while (isRoleMenuRunning)
    {
        clearConsole();
        timeshow();
        printCentered("User Role Selection");
        printCentered("=============================================");
        printCentered("1. Student");
        printCentered("2. Employment");
        printCentered("3. Entrepreneur");
        printCentered("4. Athlete");
        printCentered("5. Homemaker");
        printCentered("6. Retiree");
        printCentered("7. Miscellaneous");
        printCentered("8. Quit");
        printCentered("=============================================");

        int roleChoice;
        cout << "Enter your choice: ";
        cin >> roleChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (roleChoice)
        {
        case 1:
            printCentered("You selected Student.");
            showStudentPanel(username);
            break;
        case 2:
            printCentered("You selected Employment.");
            showEmploymentPanel();
            break;
        case 3:
            printCentered("You selected Entrepreneur.");
            handleEntrepreneurMenu();
            break;
        case 4:
            printCentered("You selected Athlete.");
            handleAthleteMenu(); // Call athlete menu function
            break;
        case 5:
            printCentered("You selected Homemaker.");
            homemakerMenu();
            break;
        case 6:
            printCentered("You selected Retiree.");
            retireeMenu();

            break;
        case 7:
            printCentered("You selected Miscellaneous.");
            handleMiscellaneous();
            break;
        case 8:
            isRoleMenuRunning = false;
            break;
        default:
            printCentered("Invalid choice. Please try again.");
            break;
        }

        if (roleChoice != 8)
        {
            printCentered("Press Enter to continue...");
            cin.get();
        }
    }
}

// Function to handle athlete menu
void handleAthleteMenu()
{
    bool isAthleteMenuRunning = true;

    while (isAthleteMenuRunning)
    {
        clearConsole();
        timeshow();
        printCentered("Athlete Menu");
        printCentered("=============================================");
        printCentered("1. Training Schedule");
        printCentered("2. Performance Tracking");
        printCentered("3. Nutrition Planning");
        printCentered("4. Back to User Role Selection");
        printCentered("=============================================");

        int athleteChoice;
        cout << "Enter your choice: ";
        cin >> athleteChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (athleteChoice)
        {
        case 1:
            handleTrainingSchedule();
            break;
        case 2:
            handlePerformanceTracking();
            break;
        case 3:
            handleNutritionPlanning();
            break;
        case 4:
            isAthleteMenuRunning = false;
            break;
        default:
            printCentered("Invalid choice. Please try again.");
            break;
        }

        if (athleteChoice != 4)
        {
            printCentered("Press Enter to continue...");
            cin.get();
        }
    }
}
// Function to handle training schedule

void handleTrainingSchedule()
{
    clearConsole();
    timeshow();
    printCentered("Training Schedule");
    printCentered("=================");

    // Implementing training schedule functionality
    // Example: Allow athletes to add, view, edit, and delete training sessions
    vector<string> trainingSessions; // Example storage for training sessions

    int choice;
    do
    {
        clearConsole();
        timeshow();
        printCentered("Training Schedule");
        printCentered("=================");
        printCentered("1. Add Training Session");
        printCentered("2. View Training Sessions");
        printCentered("3. Edit Training Session");
        printCentered("4. Delete Training Session");
        printCentered("5. Back to Athlete Menu");
        printCentered("=================");

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice)
        {
        case 1:
        {
            string session;
            cout << "Enter training session details: ";
            getline(cin, session);
            trainingSessions.push_back(session);
            printCentered("Training session added!");
            break;
        }
        case 2:
        {
            if (trainingSessions.empty())
            {
                printCentered("No training sessions added yet.");
            }
            else
            {
                printCentered("Training Sessions:");
                for (const auto& session : trainingSessions)
                {
                    printCentered("- " + session);
                }
            }
            break;
        }
        case 3:
        {
            if (trainingSessions.empty())
            {
                printCentered("No training sessions added yet.");
            }
            else
            {
                printCentered("Enter session number to edit (1-" + to_string(trainingSessions.size()) + "): ");
                int sessionNumber;
                cin >> sessionNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (sessionNumber >= 1 && sessionNumber <= trainingSessions.size())
                {
                    string newSession;
                    cout << "Enter new training session details: ";
                    getline(cin, newSession);
                    trainingSessions[sessionNumber - 1] = newSession;
                    printCentered("Training session updated!");
                }
                else
                {
                    printCentered("Invalid session number.");
                }
            }
            break;
        }
        case 4:
        {
            if (trainingSessions.empty())
            {
                printCentered("No training sessions added yet.");
            }
            else
            {
                printCentered("Enter session number to delete (1-" + to_string(trainingSessions.size()) + "): ");
                int sessionNumber;
                cin >> sessionNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (sessionNumber >= 1 && sessionNumber <= trainingSessions.size())
                {
                    trainingSessions.erase(trainingSessions.begin() + sessionNumber - 1);
                    printCentered("Training session deleted!");
                }
                else
                {
                    printCentered("Invalid session number.");
                }
            }
            break;
        }
        case 5:
        {
            return; // Return to athlete menu
        }
        default:
        {
            printCentered("Invalid choice. Please try again.");
            break;
        }
        }

        printCentered("Press Enter to continue...");
        cin.get();
    }
    while (true);
}

// Function to handle performance tracking
void handlePerformanceTracking()
{
    clearConsole();
    timeshow();
    printCentered("Performance Tracking");
    printCentered("====================");

    // Implementing performance tracking functionality
    // Example: Allow athletes to track metrics like time, distance, speed, etc.
    struct PerformanceMetric
    {
        string date;
        string activity;
        double value;
    };

    vector<PerformanceMetric> performanceMetrics; // Example storage for performance metrics

    int choice;
    do
    {
        clearConsole();
        timeshow();
        printCentered("Performance Tracking");
        printCentered("====================");
        printCentered("1. Add Performance Metric");
        printCentered("2. View Performance Metrics");
        printCentered("3. Edit Performance Metric");
        printCentered("4. Delete Performance Metric");
        printCentered("5. Back to Athlete Menu");
        printCentered("====================");

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice)
        {
        case 1:
        {
            PerformanceMetric metric;
            cout << "Enter date (DD-MM-YYYY): ";
            getline(cin, metric.date);
            cout << "Enter activity: ";
            getline(cin, metric.activity);
            cout << "Enter value: ";
            cin >> metric.value;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            performanceMetrics.push_back(metric);
            printCentered("Performance metric added!");
            break;
        }
        case 2:
        {
            if (performanceMetrics.empty())
            {
                printCentered("No performance metrics added yet.");
            }
            else
            {
                printCentered("Performance Metrics:");
                for (const auto& metric : performanceMetrics)
                {
                    printCentered("- Date: " + metric.date + ", Activity: " + metric.activity + ", Value: " + to_string(metric.value));
                }
            }
            break;
        }
        case 3:
        {
            if (performanceMetrics.empty())
            {
                printCentered("No performance metrics added yet.");
            }
            else
            {
                printCentered("Enter metric number to edit (1-" + to_string(performanceMetrics.size()) + "): ");
                int metricNumber;
                cin >> metricNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (metricNumber >= 1 && metricNumber <= performanceMetrics.size())
                {
                    PerformanceMetric& metric = performanceMetrics[metricNumber - 1];
                    cout << "Enter new date (DD-MM-YYYY, leave blank to keep current '" << metric.date << "'): ";
                    string newDate;
                    getline(cin, newDate);
                    if (!newDate.empty())
                    {
                        metric.date = newDate;
                    }
                    cout << "Enter new activity (leave blank to keep current '" << metric.activity << "'): ";
                    string newActivity;
                    getline(cin, newActivity);
                    if (!newActivity.empty())
                    {
                        metric.activity = newActivity;
                    }
                    cout << "Enter new value (leave blank to keep current '" << metric.value << "'): ";
                    string newValueStr;
                    getline(cin, newValueStr);
                    if (!newValueStr.empty())
                    {
                        metric.value = stod(newValueStr);
                    }
                    printCentered("Performance metric updated!");
                }
                else
                {
                    printCentered("Invalid metric number.");
                }
            }
            break;
        }
        case 4:
        {
            if (performanceMetrics.empty())
            {
                printCentered("No performance metrics added yet.");
            }
            else
            {
                printCentered("Enter metric number to delete (1-" + to_string(performanceMetrics.size()) + "): ");
                int metricNumber;
                cin >> metricNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (metricNumber >= 1 && metricNumber <= performanceMetrics.size())
                {
                    performanceMetrics.erase(performanceMetrics.begin() + metricNumber - 1);
                    printCentered("Performance metric deleted!");
                }
                else
                {
                    printCentered("Invalid metric number.");
                }
            }
            break;
        }
        case 5:
        {
            return; // Return to athlete menu
        }
        default:
        {
            printCentered("Invalid choice. Please try again.");
            break;
        }
        }

        printCentered("Press Enter to continue...");
        cin.get();
    }
    while (true);
}
// Function to handle nutrition planning
void handleNutritionPlanning()
{
    clearConsole();
    timeshow();
    printCentered("Nutrition Planning");
    printCentered("==================");

    // Implementing nutrition planning functionality
    // Example: Allow athletes to plan and track their daily meals
    struct Meal
    {
        string time;
        string mealName;
    };

    vector<Meal> meals; // Example storage for meals

    int choice;
    do
    {
        clearConsole();
        timeshow();
        printCentered("Nutrition Planning");
        printCentered("==================");
        printCentered("1. Plan a Meal");
        printCentered("2. View Planned Meals");
        printCentered("3. Edit Planned Meal");
        printCentered("4. Delete Planned Meal");
        printCentered("5. Back to Athlete Menu");
        printCentered("==================");

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice)
        {
        case 1:
        {
            Meal meal;
            cout << "Enter time (e.g., Breakfast, Lunch, Dinner): ";
            getline(cin, meal.time);
            cout << "Enter meal name: ";
            getline(cin, meal.mealName);
            meals.push_back(meal);
            printCentered("Meal planned!");
            break;
        }
        case 2:
        {
            if (meals.empty())
            {
                printCentered("No meals planned yet.");
            }
            else
            {
                printCentered("Planned Meals:");
                for (const auto& meal : meals)
                {
                    printCentered("- Time: " + meal.time + ", Meal: " + meal.mealName);
                }
            }
            break;
        }
        case 3:
        {
            if (meals.empty())
            {
                printCentered("No meals planned yet.");
            }
            else
            {
                printCentered("Enter meal number to edit (1-" + to_string(meals.size()) + "): ");
                int mealNumber;
                cin >> mealNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (mealNumber >= 1 && mealNumber <= meals.size())
                {
                    Meal& meal = meals[mealNumber - 1];
                    cout << "Enter new time (leave blank to keep current '" << meal.time << "'): ";
                    string newTime;
                    getline(cin, newTime);
                    if (!newTime.empty())
                    {
                        meal.time = newTime;
                    }
                    cout << "Enter new meal name (leave blank to keep current '" << meal.mealName << "'): ";
                    string newMealName;
                    getline(cin, newMealName);
                    if (!newMealName.empty())
                    {
                        meal.mealName = newMealName;
                    }
                    printCentered("Meal updated!");
                }
                else
                {
                    printCentered("Invalid meal number.");
                }
            }
            break;
        }
        case 4:
        {
            if (meals.empty())
            {
                printCentered("No meals planned yet.");
            }
            else
            {
                printCentered("Enter meal number to delete (1-" + to_string(meals.size()) + "): ");
                int mealNumber;
                cin >> mealNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (mealNumber >= 1 && mealNumber <= meals.size())
                {
                    meals.erase(meals.begin() + mealNumber - 1);
                    printCentered("Meal deleted!");
                }
                else
                {
                    printCentered("Invalid meal number.");
                }
            }
            break;
        }
        case 5:
        {
            return; // Return to athlete menu
        }
        default:
        {
            printCentered("Invalid choice. Please try again.");
            break;
        }
        }

        printCentered("Press Enter to continue...");
        cin.get();
    }
    while (true);
}

void retireeMenu()
{
    int choice;
    do
    {
        clearConsole();
        timeshow();
        printCentered("Retiree Menu");
        printCentered("=================");
        printCentered("1. Health Tracking");
        printCentered("2. Retirement Planning");
        printCentered("3. Back to Main Menu");
        printCentered("=================");

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice)
        {
        case 1:
            handleHealthTracking();
            break;
        case 2:
            // Placeholder for Retirement Planning (to be implemented)
            printCentered("Retirement Planning (To be implemented)");
            printCentered("Press Enter to continue...");
            cin.get();
            break;
        case 3:
            return; // Return to main menu
        default:
            printCentered("Invalid choice. Please try again.");
            printCentered("Press Enter to continue...");
            cin.get();
            break;
        }
    }
    while (true);
}

void handleHealthTracking()
{
    int choice;
    do
    {
        clearConsole();
        timeshow();
        printCentered("Health Tracking");
        printCentered("================");
        printCentered("1. Add Health Entry");
        printCentered("2. View Health Entries");
        printCentered("3. Edit Health Entry");
        printCentered("4. Delete Health Entry");
        printCentered("5. Record Health Metric");
        printCentered("6. View Health Metrics");
        printCentered("7. Back to Retiree Menu");
        printCentered("================");

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice)
        {
        case 1:
            addHealthEntry();
            break;
        case 2:
            viewHealthEntries();
            break;
        case 3:
            editHealthEntry();
            break;
        case 4:
            deleteHealthEntry();
            break;
        case 5:
            recordHealthMetric();
            break;
        case 6:
            viewHealthMetrics();
            break;
        case 7:
            return; // Return to retiree menu
        default:
            printCentered("Invalid choice. Please try again.");
            break;
        }

        printCentered("Press Enter to continue...");
        cin.get();
    }
    while (true);
}

void recordHealthMetric()
{
    clearConsole();
    timeshow();
    printCentered("Record Health Metric");
    printCentered("====================");

    HealthMetric metric;
    cout << "Enter date (DD-MM-YYYY): ";
    getline(cin, metric.date);
    cout << "Enter metric name (e.g., Blood Pressure, Heart Rate, Weight): ";
    getline(cin, metric.metricName);
    cout << "Enter value: ";
    cin >> metric.value;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    healthMetrics.push_back(metric);
    printCentered("Health metric recorded!");
}

void addHealthEntry()
{
    HealthEntry entry;
    cout << "Enter date (DD-MM-YYYY): ";
    getline(cin, entry.date);
    cout << "Enter category (e.g., Exercise, Medication): ";
    getline(cin, entry.category);
    cout << "Enter details: ";
    getline(cin, entry.details);
    healthEntries.push_back(entry);
    printCentered("Health entry added!");
}

void viewHealthEntries()
{
    if (healthEntries.empty())
    {
        printCentered("No health entries added yet.");
    }
    else
    {
        printCentered("Health Entries:");
        for (const auto& entry : healthEntries)
        {
            printCentered("- Date: " + entry.date + ", Category: " + entry.category + ", Details: " + entry.details);
        }
    }
}

void editHealthEntry()
{
    if (healthEntries.empty())
    {
        printCentered("No health entries added yet.");
    }
    else
    {
        printCentered("Enter entry number to edit (1-" + to_string(healthEntries.size()) + "): ");
        int entryNumber;
        cin >> entryNumber;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        if (entryNumber >= 1 && entryNumber <= healthEntries.size())
        {
            HealthEntry& entry = healthEntries[entryNumber - 1];
            cout << "Enter new date (DD-MM-YYYY, leave blank to keep current '" << entry.date << "'): ";
            string newDate;
            getline(cin, newDate);
            if (!newDate.empty())
            {
                entry.date = newDate;
            }
            cout << "Enter new category (leave blank to keep current '" << entry.category << "'): ";
            string newCategory;
            getline(cin, newCategory);
            if (!newCategory.empty())
            {
                entry.category = newCategory;
            }
            cout << "Enter new details (leave blank to keep current '" << entry.details << "'): ";
            string newDetails;
            getline(cin, newDetails);
            if (!newDetails.empty())
            {
                entry.details = newDetails;
            }
            printCentered("Health entry updated!");
        }
        else
        {
            printCentered("Invalid entry number.");
        }
    }
}

void deleteHealthEntry()
{
    if (healthEntries.empty())
    {
        printCentered("No health entries added yet.");
    }
    else
    {
        printCentered("Enter entry number to delete (1-" + to_string(healthEntries.size()) + "): ");
        int entryNumber;
        cin >> entryNumber;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        if (entryNumber >= 1 && entryNumber <= healthEntries.size())
        {
            healthEntries.erase(healthEntries.begin() + entryNumber - 1);
            printCentered("Health entry deleted!");
        }
        else
        {
            printCentered("Invalid entry number.");
        }
    }
}
void viewHealthMetrics()
{
    if (healthMetrics.empty())
    {
        printCentered("No health metrics recorded yet.");
    }
    else
    {
        printCentered("Health Metrics:");
        for (const auto& metric : healthMetrics)
        {
            printCentered("- Date: " + metric.date + ", Metric: " + metric.metricName + ", Value: " + to_string(metric.value));
        }
    }
}
void handleEntrepreneurMenu()
{
    bool isEntrepreneurMenuRunning = true;

    while (isEntrepreneurMenuRunning)
    {
        clearConsole();
        timeshow();
        printCentered("Entrepreneur Menu");
        printCentered("=============================================");
        printCentered("1. Business Ideas");
        printCentered("2. Investments");
        printCentered("3. Networking");
        printCentered("4. Back to User Role Selection");
        printCentered("=============================================");

        int entrepreneurChoice;
        cout << "Enter your choice: ";
        cin >> entrepreneurChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (entrepreneurChoice)
        {
        case 1:
            handleBusinessIdeas();
            break;
        case 2:
            handleInvestments();
            break;
        case 3:
            handleNetworking();
            break;
        case 4:
            isEntrepreneurMenuRunning = false;
            break;
        default:
            printCentered("Invalid choice. Please try again.");
            break;
        }

        if (entrepreneurChoice != 4)
        {
            printCentered("Press Enter to continue...");
            cin.get();
        }
    }
}

// Function to handle business ideas
void handleBusinessIdeas()
{
    clearConsole();
    timeshow();
    printCentered("Business Ideas");
    printCentered("=================");

    int choice;
    do
    {
        clearConsole();
        timeshow();
        printCentered("Business Ideas");
        printCentered("=================");
        printCentered("1. Add Business Idea");
        printCentered("2. View Business Ideas");
        printCentered("3. Edit Business Idea");
        printCentered("4. Delete Business Idea");
        printCentered("5. Back to Entrepreneur Menu");
        printCentered("=================");

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice)
        {
        case 1:
        {
            BusinessIdea idea;
            cout << "Enter business idea details: ";
            getline(cin, idea.details);
            businessIdeas.push_back(idea);
            printCentered("Business idea added!");
            break;
        }
        case 2:
        {
            if (businessIdeas.empty())
            {
                printCentered("No business ideas added yet.");
            }
            else
            {
                printCentered("Business Ideas:");
                for (const auto& idea : businessIdeas)
                {
                    printCentered("- " + idea.details);
                }
            }
            break;
        }
        case 3:
        {
            if (businessIdeas.empty())
            {
                printCentered("No business ideas added yet.");
            }
            else
            {
                printCentered("Enter idea number to edit (1-" + to_string(businessIdeas.size()) + "): ");
                int ideaNumber;
                cin >> ideaNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (ideaNumber >= 1 && ideaNumber <= businessIdeas.size())
                {
                    string newIdea;
                    cout << "Enter new business idea details: ";
                    getline(cin, newIdea);
                    businessIdeas[ideaNumber - 1].details = newIdea;
                    printCentered("Business idea updated!");
                }
                else
                {
                    printCentered("Invalid idea number.");
                }
            }
            break;
        }
        case 4:
        {
            if (businessIdeas.empty())
            {
                printCentered("No business ideas added yet.");
            }
            else
            {
                printCentered("Enter idea number to delete (1-" + to_string(businessIdeas.size()) + "): ");
                int ideaNumber;
                cin >> ideaNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (ideaNumber >= 1 && ideaNumber <= businessIdeas.size())
                {
                    businessIdeas.erase(businessIdeas.begin() + ideaNumber - 1);
                    printCentered("Business idea deleted!");
                }
                else
                {
                    printCentered("Invalid idea number.");
                }
            }
            break;
        }
        case 5:
        {
            return; // Return to entrepreneur menu
        }
        default:
        {
            printCentered("Invalid choice. Please try again.");
            break;
        }
        }

        printCentered("Press Enter to continue...");
        cin.get();
    }
    while (true);
}

// Function to handle investments
void handleInvestments()
{
    clearConsole();
    timeshow();
    printCentered("Investments");
    printCentered("====================");

    int choice;
    do
    {
        clearConsole();
        timeshow();
        printCentered("Investments");
        printCentered("====================");
        printCentered("1. Add Investment");
        printCentered("2. View Investments");
        printCentered("3. Edit Investment");
        printCentered("4. Delete Investment");
        printCentered("5. Back to Entrepreneur Menu");
        printCentered("====================");

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice)
        {
        case 1:
        {
            Investment investment;
            cout << "Enter investment name: ";
            getline(cin, investment.name);
            cout << "Enter investment amount: ";
            cin >> investment.amount;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            investments.push_back(investment);
            printCentered("Investment added!");
            break;
        }
        case 2:
        {
            if (investments.empty())
            {
                printCentered("No investments added yet.");
            }
            else
            {
                printCentered("Investments:");
                for (const auto& investment : investments)
                {
                    printCentered("- Name: " + investment.name + ", Amount: " + to_string(investment.amount));
                }
            }
            break;
        }
        case 3:
        {
            if (investments.empty())
            {
                printCentered("No investments added yet.");
            }
            else
            {
                printCentered("Enter investment number to edit (1-" + to_string(investments.size()) + "): ");
                int investmentNumber;
                cin >> investmentNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (investmentNumber >= 1 && investmentNumber <= investments.size())
                {
                    Investment& investment = investments[investmentNumber - 1];
                    cout << "Enter new investment name (leave blank to keep current '" << investment.name << "'): ";
                    string newName;
                    getline(cin, newName);
                    if (!newName.empty())
                    {
                        investment.name = newName;
                    }
                    cout << "Enter new investment amount (leave blank to keep current '" << investment.amount << "'): ";
                    string newAmountStr;
                    getline(cin, newAmountStr);
                    if (!newAmountStr.empty())
                    {
                        investment.amount = stod(newAmountStr);
                    }
                    printCentered("Investment updated!");
                }
                else
                {
                    printCentered("Invalid investment number.");
                }
            }
            break;
        }
        case 4:
        {
            if (investments.empty())
            {
                printCentered("No investments added yet.");
            }
            else
            {
                printCentered("Enter investment number to delete (1-" + to_string(investments.size()) + "): ");
                int investmentNumber;
                cin >> investmentNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (investmentNumber >= 1 && investmentNumber <= investments.size())
                {
                    investments.erase(investments.begin() + investmentNumber - 1);
                    printCentered("Investment deleted!");
                }
                else
                {
                    printCentered("Invalid investment number.");
                }
            }
            break;
        }
        case 5:
        {
            return; // Return to entrepreneur menu
        }
        default:
        {
            printCentered("Invalid choice. Please try again.");
            break;
        }
        }

        printCentered("Press Enter to continue...");
        cin.get();
    }
    while (true);
}
// Function to handle networking
void handleNetworking()
{
    clearConsole();
    timeshow();
    printCentered("Networking");
    printCentered("====================");

    int choice;
    do
    {
        clearConsole();
        timeshow();
        printCentered("Networking");
        printCentered("====================");
        printCentered("1. Add Contact");
        printCentered("2. View Contacts");
        printCentered("3. Edit Contact");
        printCentered("4. Delete Contact");
        printCentered("5. Back to Entrepreneur Menu");
        printCentered("====================");

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice)
        {
        case 1:
        {
            Contact contact;
            cout << "Enter contact name: ";
            getline(cin, contact.name);
            cout << "Enter company: ";
            getline(cin, contact.company);
            cout << "Enter position: ";
            getline(cin, contact.position);
            contacts.push_back(contact);
            printCentered("Contact added!");
            break;
        }
        case 2:
        {
            if (contacts.empty())
            {
                printCentered("No contacts added yet.");
            }
            else
            {
                printCentered("Contacts:");
                for (const auto& contact : contacts)
                {
                    printCentered("- Name: " + contact.name + ", Company: " + contact.company + ", Position: " + contact.position);
                }
            }
            break;
        }
        case 3:
        {
            if (contacts.empty())
            {
                printCentered("No contacts added yet.");
            }
            else
            {
                printCentered("Enter contact number to edit (1-" + to_string(contacts.size()) + "): ");
                int contactNumber;
                cin >> contactNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (contactNumber >= 1 && contactNumber <= contacts.size())
                {
                    Contact& contact = contacts[contactNumber - 1];
                    cout << "Enter new contact name (leave blank to keep current '" << contact.name << "'): ";
                    string newName;
                    getline(cin, newName);
                    if (!newName.empty())
                    {
                        contact.name = newName;
                    }
                    cout << "Enter new company (leave blank to keep current '" << contact.company << "'): ";
                    string newCompany;
                    getline(cin, newCompany);
                    if (!newCompany.empty())
                    {
                        contact.company = newCompany;
                    }
                    cout << "Enter new position (leave blank to keep current '" << contact.position << "'): ";
                    string newPosition;
                    getline(cin, newPosition);
                    if (!newPosition.empty())
                    {
                        contact.position = newPosition;
                    }
                    printCentered("Contact updated!");
                }
                else
                {
                    printCentered("Invalid contact number.");
                }
            }
            break;
        }
        case 4:
        {
            if (contacts.empty())
            {
                printCentered("No contacts added yet.");
            }
            else
            {
                printCentered("Enter contact number to delete (1-" + to_string(contacts.size()) + "): ");
                int contactNumber;
                cin >> contactNumber;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                if (contactNumber >= 1 && contactNumber <= contacts.size())
                {
                    contacts.erase(contacts.begin() + contactNumber - 1);
                    printCentered("Contact deleted!");
                }
                else
                {
                    printCentered("Invalid contact number.");
                }
            }
            break;
        }
        case 5:
        {
            return; // Return to entrepreneur menu
        }
        default:
        {
            printCentered("Invalid choice. Please try again.");
            break;
        }
        }

        printCentered("Press Enter to continue...");
        cin.get();
    }
    while (true);
}


void showMainMenu()
{
    bool isRunning = true;
    bool loginSuccess = false;

    string loggedInUser;
    while (isRunning)
    {
        clearConsole();
        timeshow();
        cout << endl << endl << endl << endl << endl << endl;
        printCentered("Main Menu");
        printCentered("=============================================");
        printCentered("Already Have an Account");
        printCentered("1. Login");
        cout << endl;
        printCentered("If you are new to this App, Please signup");
        printCentered("2. Sign Up");
        cout << endl;
        printCentered("3. Exit");
        printCentered("=============================================");

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice)
        {
        case 1:
            loginSuccess = showLoginPanel(loggedInUser);
            if (loginSuccess)
            {
                //showUserMenu(loggedInUser);
            }
            break;
        case 2:
            showSignUpPanel();
            break;
        case 3:
            isRunning = false;
            break;
        default:
            printCentered("Invalid choice. Please try again.");
            printCentered("Press Enter to continue...");
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            cin.get();
            break;
        }
    }

    if (loginSuccess)
    {
        printCentered("Access granted. Welcome to the system!");
    }
    else
    {
        printCentered("Goodbye!");
    }
}
void handleMiscellaneous() {
    vector<Reminder2> reminders;

    int choice;
    do {
        clearConsole();
        timeshow();
        printCentered("Miscellaneous - Reminder/Alarm");
        printCentered("==============================");
        printCentered("1. Add a Time and Description");
        printCentered("2. See How Much Time Left");
        printCentered("3. Back to Main Menu");
        printCentered("==============================");

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
            case 1: {
                clearConsole();
                timeshow();
                printCentered("Add a Time and Description");
                printCentered("==========================");

                Reminder2 newReminder;
                int hour, minute, second;

                cout << "Enter hour (0-23): ";
                cin >> hour;
                cout << "Enter minute (0-59): ";
                cin >> minute;
                cout << "Enter second (0-59): ";
                cin >> second;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                time_t now = time(nullptr); // Declare now here
                tm* localTime = localtime(&now);
                newReminder.time.tm_hour = hour;
                newReminder.time.tm_min = minute;
                newReminder.time.tm_sec = second;
                newReminder.time.tm_isdst = -1; // Set to default value
                newReminder.time.tm_year = localtime(&now)->tm_year; // Ensure year is current year
                newReminder.time.tm_mon = localtime(&now)->tm_mon; // Ensure month is current month
                newReminder.time.tm_mday = localtime(&now)->tm_mday; // Ensure day is current day

                cout << "Enter description: ";
                getline(cin, newReminder.description);

                reminders.push_back(newReminder);
                printCentered("Reminder added!");
                break;
            }
            case 2: {
                clearConsole();
                timeshow();
                printCentered("Time Left for Reminders");
                printCentered("=======================");

                if (reminders.empty()) {
                    printCentered("No reminders set.");
                } else {
                    time_t now = time(nullptr);
                    tm* localTime = localtime(&now);

                    for (const auto& reminder : reminders) {
                        tm reminderTime = reminder.time; // Make a non-const copy
                        time_t reminderTimeT = mktime(&reminderTime);
                        double secondsLeft = difftime(reminderTimeT, now);

                        if (secondsLeft < 0) {
                            printCentered(reminder.description + ": Finished");
                        } else {
                            int hoursLeft = secondsLeft / 3600;
                            int minutesLeft = ((int)secondsLeft % 3600) / 60;
                            int secondsLeftInt = (int)secondsLeft % 60;

                            printCentered(reminder.description + ": " +
                                to_string(hoursLeft) + " hours " +
                                to_string(minutesLeft) + " minutes " +
                                to_string(secondsLeftInt) + " seconds left");
                        }
                    }
                }
                break;
            }
            case 3: {
                return; // Return to main menu
            }
            default: {
                cout<<endl<<endl;
                printCentered("Invalid choice. Please try again.");
                break;
            }
        }
        cout<<endl<<endl<<endl;
        printCentered("Press Enter to continue...");
        cin.get();
    } while (true);
}
void addStudySession(const string& username) {
    clearConsole();
    timeshow();
    cout << endl << endl;
    printCentered("Add Study Session");
    printCentered("==================");

    while (true) {
        StudySession session;
        cout << "Enter subject: ";
        getline(cin, session.subject);

        cout << "Enter start time (HH:MM): ";
        getline(cin, session.startTime);

        cout << "Enter end time (HH:MM): ";
        getline(cin, session.endTime);
        studySchedules[username].push_back(session);

        printCentered("Study session added successfully!");

        cout << "Do you want to add another study session? (yes/no): ";
        string addAnother;
        getline(cin, addAnother);

        if (addAnother != "yes" && addAnother != "Yes") {
            break; // Exit the loop if user does not want to add another session
        }

        clearConsole();
        timeshow();
        cout << endl << endl;
        printCentered("Add Study Session");
        printCentered("==================");
    }

    printCentered("Press Enter to return to the Student Panel...");
    cin.get();
}
void showStudySchedule(const string& username) {
    clearConsole();
    timeshow();
    cout << endl << endl;
    printCentered("Your Study Schedule");
    printCentered("====================");

    if (studySchedules.find(username) != studySchedules.end() && !studySchedules[username].empty()) {
        for (const auto& session : studySchedules[username]) {
            printBox("Subject: " + session.subject + "\nTime: " + session.startTime + " - " + session.endTime);
        }
    } else {
        printCentered("No study sessions found.");
    }

    printCentered("Press Enter to return to the Student Panel...");
    cin.get();
}
void setReminder(const string& username) {
    clearConsole();
    timeshow();
    cout << endl << endl;
    printCentered("Set a Reminder");
    printCentered("================");

    Reminder reminder;
    cout << "Enter reminder message: ";
    getline(cin, reminder.message);

    string dateTime;
    cout << "Enter date and time (YYYY-MM-DD HH:MM): ";
    getline(cin, dateTime);

    istringstream ss(dateTime);
    ss >> get_time(&reminder.reminderTime, "%Y-%m-%d %H:%M");

    reminders[username].push_back(reminder);

    printCentered("Reminder set successfully!");
    printCentered("Press Enter to return to the Student Panel...");
    cin.get();
}
void showReminders(const string& username) {
    clearConsole();
    timeshow();
    cout << endl << endl;
    printCentered("Your Reminders");
    printCentered("================");

    if (reminders.find(username) != reminders.end() && !reminders[username].empty()) {
        for (const auto& reminder : reminders[username]) {
            ostringstream oss;
            oss << put_time(&reminder.reminderTime, "%Y-%m-%d %H:%M");
            printBox("Reminder: " + reminder.message + "\nTime: " + oss.str());
        }
    } else {
        printCentered("No reminders found.");
    }

    printCentered("Press Enter to return to the Student Panel...");
         cin.get();
}
void checkReminders(const string& username) {
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);

    if (reminders.find(username) != reminders.end() && !reminders[username].empty()) {
        auto& userReminders = reminders[username];
        for (auto it = userReminders.begin(); it != userReminders.end(); ) {
            if (difftime(mktime(&it->reminderTime), mktime(localTime)) <= 0) {
                MessageBox(NULL, it->message.c_str(), "Reminder", MB_OK | MB_ICONINFORMATION);
                it = userReminders.erase(it); // Remove triggered reminder
            } else {
                ++it;
            }
        }
    }
}
void addNote(const string& username) {
    clearConsole();
    timeshow();
    cout << endl << endl;
    printCentered("Take a Note");
    printCentered("================");

    Note note;
    cout << "Enter your note: ";
    getline(cin, note.content);

    // Optionally, you can add a timestamp
    // note.timestamp = getCurrentDateTime(); // Implement getCurrentDateTime() as needed

    userNotes[username].push_back(note);

    printCentered("Note added successfully!");
    printCentered("Press Enter to return to the Student Panel...");
    cin.get();
}
void showNotes(const string& username) {
    clearConsole();
    timeshow();
    cout << endl << endl;
    printCentered("Your Notes");
    printCentered("================");

    if (userNotes.find(username) != userNotes.end() && !userNotes[username].empty()) {
        for (const auto& note : userNotes[username]) {
            printBox("Timestamp: " + note.timestamp + "\nNote: " + note.content);
        }
    } else {
        printCentered("No notes found.");
    }

    printCentered("Press Enter to return to the Student Panel...");
    cin.get();
}
void clearUserData(const string& username) {
    clearConsole();
    timeshow();
    cout << endl << endl;
    printCentered("Erase Everything");
    printCentered("==================");

    cout << "Are you sure you want to erase everything? This action cannot be undone. (yes/no): ";
    string confirmation;
    getline(cin, confirmation);

    if (confirmation == "yes" || confirmation == "Yes") {
        // Clear all user data
        timetables.erase(username);
        //mealTimetables.erase(username);
        reminders.erase(username);
        userNotes.erase(username);
        studySchedules.erase(username);
        printCentered("All data erased successfully.");
    } else {
        printCentered("Action cancelled.");
    }

    printCentered("Press Enter to return to the Student Panel...");
    cin.get();
}
bool parseDateTime(const string& timeStr, const string& dateStr, tm& dateTime) {
    stringstream ss(timeStr + " " + dateStr);
    ss >> get_time(&dateTime, "%H:%M %d-%m-%Y");
    return !ss.fail();
}

void addBusSchedule(vector<TimetableEntry>& busSchedules) {
    while (true) {
        clearConsole();
        TimetableEntry busEntry;
        cout << "Enter bus time (HH:MM): ";
        string busTime;
        getline(cin, busTime);
        cout << "Enter bus description: ";
        getline(cin, busEntry.description);
        cout << "Enter date for the bus (DD-MM-YYYY): ";
        string busDate;
        getline(cin, busDate);

        // Combine date and time for parsing
        if (parseDateTime(busTime, busDate, busEntry.dateTime)) {
            busEntry.category = BUS_SCHEDULE; // Set category explicitly
            busSchedules.push_back(busEntry);
            printCentered("Bus schedule added successfully!");
        } else {
            printCentered("Invalid date/time format. Please try again.");
        }

        cout << "Do you want to add another bus schedule? (yes/no): ";
        string addAnother;
        getline(cin, addAnother);
        if (addAnother != "yes" && addAnother != "Yes") {
            break;
        }
    }
}

void addClassRoutine(vector<TimetableEntry>& classRoutine) {
    while (true) {
        clearConsole();
        TimetableEntry routineEntry;
        cout << "Enter subject name: ";
        getline(cin, routineEntry.subjectName); // Use subjectName for subject
        cout << "Enter teacher name: ";
        getline(cin, routineEntry.teacherName); // Use teacherName for teacher
        cout << "Enter time for the class (HH:MM): ";
        string classTime;
        getline(cin, classTime);
        cout << "Enter date for the class (DD-MM-YYYY): ";
        string classDate;
        getline(cin, classDate);

        // Combine date and time for parsing
        if (parseDateTime(classTime, classDate, routineEntry.dateTime)) {
            routineEntry.category = CLASS_ROUTINE; // Set category explicitly
            classRoutine.push_back(routineEntry);
            printCentered("Class routine added successfully!");
        } else {
            printCentered("Invalid date/time format. Please try again.");
        }

        cout << "Do you want to add another class routine? (yes/no): ";
        string addAnother;
        getline(cin, addAnother);
        if (addAnother != "yes" && addAnother != "Yes") {
            break;
        }
    }
}

void addOtherActivity(vector<TimetableEntry>& otherActivities) {
    clearConsole();
    TimetableEntry otherEntry;
    cout << "Enter description of the activity: ";
    getline(cin, otherEntry.description);
    cout << "Enter time for this activity (HH:MM): ";
    string activityTime;
    getline(cin, activityTime);
    cout << "Enter date for this activity (DD-MM-YYYY): ";
    string activityDate;
    getline(cin, activityDate);

    // Combine date and time for parsing
    if (parseDateTime(activityTime, activityDate, otherEntry.dateTime)) {
        otherEntry.category = OTHER_ACTIVITY; // Set category explicitly
        otherActivities.push_back(otherEntry);
        printCentered("Other activity added successfully!");
    } else {
        printCentered("Invalid date/time format. Please try again.");
    }
}




   void addAcademicTimetable(const string &username) {
    clearConsole();
    timeshow();
    cout << endl << endl;
    printCentered("Add Academic Timetable");
    printCentered("============================");

    while (true) {
        printCentered("1. Bus Schedule");
        printCentered("2. Class Routine");
        printCentered("3. Other Activities");
        printCentered("4. Finish");

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        vector<TimetableEntry> &userTimetable = timetables[username];

        switch (choice) {
            case 1:
                addBusSchedule(userTimetable);
                break;
            case 2:
                addClassRoutine(userTimetable);
                break;
            case 3:
                addOtherActivity(userTimetable);
                break;
            case 4:
                printCentered("Academic timetable updated successfully!");
                printCentered("Press Enter to return to the Student Panel...");
                cin.get();
                return;
            default:
                printCentered("Invalid choice. Please try again.");
                break;
        }
    }
}

void showAcademicTimetable(const string &username) {
    clearConsole();
    timeshow();
    cout << endl << endl;
    printCentered("Show Academic Timetable");
    printCentered("============================");

    if (timetables.find(username) != timetables.end() && !timetables[username].empty()) {
        const vector<TimetableEntry> &userTimetable = timetables[username];

        for (const TimetableEntry &entry : userTimetable) {
            string title;
            switch (entry.category) {
                case BUS_SCHEDULE:
                    title = "Bus Schedule";
                    break;
                case CLASS_ROUTINE:
                    title = "Class Routine";
                    break;
                case OTHER_ACTIVITY:
                    title = "Other Activities";
                    break;
                default:
                    continue; // Skip if unknown category
            }

            printCentered(title);
            printCentered("===================================");

            ostringstream oss;
            oss << put_time(&entry.dateTime, "%H:%M %d-%m-%Y");

            printBox("Time: " + oss.str());
            printBox("Description: " + entry.description);
            if (entry.category == CLASS_ROUTINE) {
                printBox("Subject: " + entry.subjectName);
                printBox("Teacher: " + entry.teacherName);
            }
            cout << endl;
        }
    } else {
        printCentered("No timetable found for this user.");
    }

    printCentered("Press Enter to return to the Student Panel...");
    cin.get();
}
void healthMenu() {
    int choice;
    do {
        clearConsole();
        timeshow();
        printCentered("Other Options");
        printCentered("=============================================");
        printCentered("1. Meal Reminder");
        printCentered("2. Drink Water Reminder");
        printCentered("3. Diet Plan");
        printCentered("4. Exercise Plan");
        printCentered("5. Take Note on Health");
        printCentered("6. Exit");
        printCentered("=============================================");
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
            case 1:
                handleNutritionPlanning();
                break;
            case 2:
                // Implement drink water reminder
                cout << "Drink water reminder functionality\n";
                cout<<endl<<endl;
                cout << "\033[1;36m";
                printCentered("Stay hydrated! Drink water regularly.");
                cout << "\033[0m"; // Reset to default
                cout<<endl<<endl;
                remindToDrinkWater();
                break;
            case 3:
                // Implement diet plan
                cout << "Diet plan functionality\n";
                handleDietPlan();
                break;
            case 4:
                // Implement exercise plan
                cout << "Exercise plan functionality\n";
                handleExercisePlan();
                break;
            case 5:
                // Implement take note on health
                cout << "Take note on health functionality\n";
                recordHealthMetric();
                break;
            case 6:
                cout << "Exiting health menu...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 6.\n";
                break;
        }

        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Wait for user to press Enter
        cin.get(); // Pause before clearing console and showing menu again

    } while (choice != 6);
}

void remindToDrinkWater() {
    // Define reminder times (in 24-hour format)
    int reminderTimes[] = {5, 8, 10, 12, 14, 16, 18, 20}; // Adjust times as needed
    int numReminders = sizeof(reminderTimes) / sizeof(reminderTimes[0]);

    while (true) {
        // Get current time
        clearConsole();
        timeshow();
        auto now = chrono::system_clock::now();
        time_t current_time = chrono::system_clock::to_time_t(now);
        tm *local_time = localtime(&current_time);

        int current_hour = local_time->tm_hour;

        // Find previous and next reminder times
        int prevReminder = reminderTimes[numReminders - 1], nextReminder = reminderTimes[0];

        for (int i = 0; i < numReminders; ++i) {
            if (reminderTimes[i] <= current_hour) {
                prevReminder = reminderTimes[i];
            }
            if (reminderTimes[i] > current_hour) {
                nextReminder = reminderTimes[i];
                break;
            }
        }

        // Handle wrap-around from end to start of the day
        if (prevReminder == nextReminder || nextReminder == reminderTimes[0]) {
            nextReminder = reminderTimes[0];
        }

        // Display current, previous, and next reminder times
        cout << "Current time: " << current_hour << ":00" << endl;
        cout << "Previous reminder time: " << prevReminder << ":00" << endl;
        cout << "Next reminder time: " << nextReminder << ":00" << endl;

        // Check if current hour matches any reminder time
        for (int i = 0; i < numReminders; ++i) {
            if (current_hour == reminderTimes[i]) {
                cout << "Reminder: Drink water! It's " << current_hour << ":00." << endl;
                // Delay for 1 minute to avoid repetitive reminders in a short time
                this_thread::sleep_for(chrono::minutes(1));
            }
        }

        // Inform the user they can press Enter to exit
        cout << "Press Enter to exit this panel.\n";

        // Use cin to wait for Enter key
        if (cin.peek() == '\n') {
            cin.ignore();
            cout << "Exiting reminder panel.\n";
            break;
        }

        // Sleep for an hour and check again
        this_thread::sleep_for(chrono::hours(1));
    }
}

void addTask() {


    Task newTask;

    printCentered("Enter time for the task (e.g., 09:00 AM): ");
    cin.ignore(); // Clear the input buffer
    getline(cin, newTask.time);
    printCentered("Enter description for the task: ");
    getline(cin, newTask.description);
    tasks.push_back(newTask);
    printCentered("Task added successfully.");
}

void viewTasks() {

    if (tasks.empty()) {
        printCentered("No tasks added yet.");
    } else {
        printCentered("Tasks for the day:");
        for (const auto& task : tasks) {
            printCentered(task.time + " - " + task.description);
        }
    }
}
void homemakerMenu() {
    int choice;
    do {
            clearConsole();
        timeshow();
        printCentered("Homemaker Menu:");
        printCentered("1. Add task for whole day");
        printCentered("2. View task for whole day");
        printCentered("3. Health");
        printCentered("4. Exit");
        printCentered("Select an option: ");
        cin >> choice;
        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                  healthMenu();
                break;
            case 4:
                printCentered("Exiting Homemaker Menu.");
                break;
            default:
                printCentered("Invalid option selected. Please try again.");
                break;
        }
    } while (choice != 4);
}





int main()
{
    showWelcomePanel();
    showMainMenu();
    return 0;
}

