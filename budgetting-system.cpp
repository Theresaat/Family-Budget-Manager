// Theresa Thompson
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits> // For numeric_limits

using namespace std;

// Struct to hold transaction details
struct Transaction {
    string type;    // "Income" or "Expense"
    string category;
    double amount;  // Transaction amount
};

// Class to manage the family budget
class FamilyBudget {
private:
    vector<Transaction> transactions;   // Store all transactions
    double balance;                     // Current balance
    vector<string> expenseCategories;   // Predefined expense categories
    int dependents;                     // Number of dependents

public:
    // Constructor to initialize the class attributes
    FamilyBudget() : balance(0.0), dependents(0) {
        // Predefined expense categories for the user
        expenseCategories = {
            "Retirement", 
            "Student Loan", 
            "Transportation", 
            "Communications", 
            "Savings", 
            "Groceries", 
            "Health Insurance"
        };
    }

    // Set the number of dependents
    void setDependents(int numDependents) {
        if (numDependents < 0) {  // Validate dependents to be non-negative
            cout << "The number of dependents cannot be negative.\n";
            return;
        }
        dependents = numDependents;
        cout << "Dependents set to: " << dependents << endl;
    }

    // Get the current number of dependents
    int getDependents() const {
        return dependents;
    }

    // Add an income transaction
    void addIncome(double amount) {
        if (amount <= 0) {  // Validate income to be positive
            cout << "Income amount must be greater than zero.\n";
            return;
        }
        transactions.push_back({"Income", "N/A", amount});  // Record the transaction
        balance += amount;  // Update balance
        cout << "Income added successfully! Your balance is now $" << fixed << setprecision(2) << balance << endl;
    }

    // Add an expense transaction
    void addExpense(const string& category, double amount) {
        if (amount <= 0) {  // Validate expense to be positive
            cout << "Expense amount must be greater than zero.\n";
            return;
        }

        // Check if the category exists
        bool validCategory = false;
        for (const auto& cat : expenseCategories) {
            if (cat == category) {
                validCategory = true;
                break;
            }
        }

        // If category does not exist, prompt user to add it
        if (!validCategory) {
            cout << "Category not found: " << category << endl;
            cout << "Would you like to add this category? (y/n): ";
            char addCategory;
            cin >> addCategory;
            if (addCategory == 'y' || addCategory == 'Y') {
                expenseCategories.push_back(category);  // Add new category
                cout << "Category added: " << category << endl;
            } else {
                cout << "Expense not recorded. Please try again with an existing category.\n";
                return;
            }
        }

        transactions.push_back({"Expense", category, amount});  // Record the transaction
        balance -= amount;  // Update balance
        cout << "Expense of $" << fixed << setprecision(2) << amount << " added under " << category << " category.\n";
        cout << "Your updated balance is: $" << fixed << setprecision(2) << balance << endl;
    }

    // Display the current balance
    void viewBalance() const {
        cout << "\n--- Current Balance ---\n";
        cout << "Your balance: $" << fixed << setprecision(2) << balance << endl;
    }

    // Display a summary of all transactions
    void viewTransactions() const {
        cout << "\n--- Transaction Summary ---\n";
        cout << left << setw(10) << "Type"          // Align columns
             << setw(20) << "Category"
             << setw(10) << "Amount" << endl;
        cout << string(40, '-') << endl;          // Separator line

        for (const auto& t : transactions) {      // Loop through all transactions
            cout << left << setw(10) << t.type
                 << setw(20) << t.category
                 << "$" << setw(10) << fixed << setprecision(2) << t.amount << endl;
        }

        cout << "\nTotal balance: $" << fixed << setprecision(2) << balance << endl;
    }

    // Display available expense categories
    void viewCategories() const {
        cout << "\n--- Available Expense Categories ---\n";
        if (expenseCategories.empty()) {  // Check if categories exist
            cout << "No categories available. Please add some categories.\n";
        } else {
            for (const auto& category : expenseCategories) {  // Print each category
                cout << "- " << category << endl;
            }
        }
    }

    // Provide financial advice based on the balance and dependents
    void giveAdvice() const {
        cout << "\n--- Financial Advice ---\n";

        if (balance < 0) {  // Advice for negative balance
            cout << "Your balance is negative. It's important to prioritize essential expenses such as savings, healthcare, and student loans.\n";
            cout << "Consider tracking your spending carefully and look for ways to cut back on non-essential expenses.\n";
        } else if (balance > 1000) {  // Advice for healthy balance
            cout << "Great job! You have a healthy balance. Consider setting up an emergency fund or investing for your future.\n";
        } else {  // Advice for moderate balance
            cout << "Keep up the good work! Try to continue saving and avoid spending too much on unnecessary items.\n";
        }

        if (dependents > 0) {  // Dependent-specific advice
            cout << "As you have " << dependents << " dependent(s), ensure their well-being is covered. Consider setting aside extra funds for healthcare and education.\n";
        } else {
            cout << "Without dependents, your financial flexibility is greater. Consider saving for future goals like home ownership or retirement.\n";
        }
    }
};

// Main function
int main() {
    cout << "Welcome to the TOK Family Budget System!\n";
    cout << "This system helps you manage your income, expenses, and provides advice to keep your finances healthy.\n\n";

    FamilyBudget budget;
    int choice;

    // Ask the user for the number of dependents
    int numDependents;
    cout << "How many dependents do you have? ";
    cin >> numDependents;
    budget.setDependents(numDependents);  // Set dependents in the system

    do {
        // Display the menu
        cout << "\n--- Family Budget Manager ---\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. View Balance\n";
        cout << "4. View Transactions\n";
        cout << "5. View Expense Categories\n";
        cout << "6. Financial Advice\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        // Validate user choice input
        if (!(cin >> choice)) {  // If input is invalid
            cout << "Invalid choice. Please enter a number between 1 and 7.\n";
            cin.clear();  // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            continue;  // Restart loop
        }

        // Handle menu choices
        switch (choice) {
            case 1: {
                double amount;
                cout << "Enter income amount: $";
                cin >> amount;

                if (cin.fail()) {  // Validate numeric input
                    cout << "Invalid amount. Please enter a valid number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                budget.addIncome(amount);  // Add income to budget
                break;
            }
            case 2: {
                string category;
                double amount;
                cout << "Enter expense category (e.g., Retirement, Student Loan, etc.): ";
                cin >> ws;  // Ignore leading whitespace
                getline(cin, category);
                cout << "Enter expense amount: $";
                cin >> amount;

                if (cin.fail()) {  // Validate numeric input
                    cout << "Invalid amount. Please enter a valid number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                budget.addExpense(category, amount);  // Add expense to budget
                break;
            }
            case 3:
                budget.viewBalance();  // Display balance
                break;
            case 4:
                budget.viewTransactions();  // Display transactions
                break;
            case 5:
                budget.viewCategories();  // Display categories
                break;
            case 6:
                budget.giveAdvice();  // Provide advice
                break;
            case 7:
                cout << "Thank you for using the TOK Family Budget System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        }
    } while (choice != 7);  // Repeat until user exits

    return 0;
}