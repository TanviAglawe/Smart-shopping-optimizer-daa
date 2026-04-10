#include <iostream>
#include <vector>
using namespace std;

struct Product {
    string name;
    int price;
    int value;
};

// Display products
void displayProducts(vector<Product>& products) {
    cout << "\n=========== PRODUCT CATALOG ===========\n";
    cout << "ID\tName\t\tPrice\tValue\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < products.size(); i++) {
        cout << i + 1 << "\t" << products[i].name 
             << "\t\t" << products[i].price 
             << "\t" << products[i].value << endl;
    }
}

// Optimize cart using Knapsack
void optimizeCart(vector<Product>& cart, int budget) {
    int n = cart.size();

    vector<vector<int>> dp(n + 1, vector<int>(budget + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= budget; w++) {
            if (cart[i - 1].price <= w) {
                dp[i][w] = max(
                    dp[i - 1][w],
                    cart[i - 1].value + dp[i - 1][w - cart[i - 1].price]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "\n=========== OPTIMIZED CART ===========\n";
    int w = budget;
    int totalCost = 0;

    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << "✔ " << cart[i - 1].name 
                 << " (Rs." << cart[i - 1].price << ")\n";
            totalCost += cart[i - 1].price;
            w -= cart[i - 1].price;
        }
    }

    cout << "--------------------------------------\n";
    cout << "Total Spent : Rs." << totalCost << endl;
    cout << "Budget Left : Rs." << (budget - totalCost) << endl;
    cout << "Total Value : " << dp[n][budget] << endl;
}

// Main
int main() {
    vector<Product> products;
    vector<Product> cart;

    int choice, n, budget, id;

    do {
        cout << "\n======================================\n";
        cout << "        SMART SHOPPING SYSTEM         \n";
        cout << "======================================\n";
        cout << "1. Enter Products\n";
        cout << "2. View Products\n";
        cout << "3. Add Product to Cart\n";
        cout << "4. View Cart\n";
        cout << "5. Optimize Cart (Knapsack)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "\nEnter number of products: ";
            cin >> n;

            products.resize(n);

            for (int i = 0; i < n; i++) {
                cout << "\nProduct " << i + 1 << " Name: ";
                cin >> products[i].name;
                cout << "Price: ";
                cin >> products[i].price;
                cout << "Value (importance): ";
                cin >> products[i].value;
            }
            break;

        case 2:
            if (products.empty()) {
                cout << "No products available!\n";
            } else {
                displayProducts(products);
            }
            break;

        case 3:
            if (products.empty()) {
                cout << "Enter products first!\n";
            } else {
                displayProducts(products);
                cout << "\nEnter product ID to add: ";
                cin >> id;

                if (id > 0 && id <= products.size()) {
                    cart.push_back(products[id - 1]);
                    cout << "✔ Added to cart!\n";
                } else {
                    cout << "Invalid ID!\n";
                }
            }
            break;

        case 4:
            cout << "\n=========== YOUR CART ===========\n";
            if (cart.empty()) {
                cout << "Cart is empty!\n";
            } else {
                for (auto &p : cart) {
                    cout << "- " << p.name << " (Rs." << p.price << ")\n";
                }
            }
            break;

        case 5:
            if (cart.empty()) {
                cout << "Cart is empty!\n";
            } else {
                cout << "\nEnter your budget: Rs.";
                cin >> budget;
                optimizeCart(cart, budget);
            }
            break;

        case 0:
            cout << "\nThank you for shopping!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}