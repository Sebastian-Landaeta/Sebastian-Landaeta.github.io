#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Product {
public:
    string main_category;
    string title;
    double average_rating;
    int rating_number;
    double price;
    string url;
};

vector<Product> extractDataFromJson(const string& filePath) {
    vector<Product> products;

    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error: Unable to open json file " << filePath << endl;
        return products;
    }

    string line;
    while (getline(file, line)) {
        Product product;

        // Find main_category
        size_t main_category_pos = line.find("\"main_category\": \"");
        if (main_category_pos != string::npos) {
            main_category_pos += 18; // Length of "\"main_category\": \""
            size_t end_quote = line.find("\"", main_category_pos);
            product.main_category = line.substr(main_category_pos, end_quote - main_category_pos);
        }

        // Find title
        size_t title_pos = line.find("\"title\": \"");
        if (title_pos != string::npos) {
            title_pos += 10; // Length of "\"title\": \""
            size_t end_quote = line.find("\"", title_pos);
            product.title = line.substr(title_pos, end_quote - title_pos);
        }

        // Find average_rating
        size_t rating_pos = line.find("\"average_rating\": ");
        if (rating_pos != string::npos) {
            rating_pos += 18; // Length of "\"average_rating\": "
            size_t end_value = line.find(",", rating_pos);
            string rating_str = line.substr(rating_pos, end_value - rating_pos);
            product.average_rating = stod(rating_str);
        }

        // Find rating_number
        size_t num_pos = line.find("\"rating_number\": ");
        if (num_pos != string::npos) {
            num_pos += 16; // Length of "\"rating_number\": "
            size_t end_value = line.find(",", num_pos);
            string num_str = line.substr(num_pos, end_value - num_pos);
            product.rating_number = stoi(num_str);
        }

        // Find price
        size_t price_pos = line.find("\"price\": ");
        if (price_pos != string::npos) {
            price_pos += 9; // Length of "\"price\": "
            size_t end_value = line.find(",", price_pos);
            string price_str = line.substr(price_pos, end_value - price_pos);
            if (price_str != "null") {
                product.price = stod(price_str);
            }
            else{
                product.price = -1;
            }
        }

        // Find URL
        size_t url_pos = line.find("\"thumb\": \"");
        if (url_pos != string::npos) {
            url_pos += 10; // Length of "\"thumb\": \""
            size_t end_quote = line.find("\"", url_pos);
            product.url = line.substr(url_pos, end_quote - url_pos);
        }

        products.push_back(product);
    }

    file.close();

    return products;
}

void filterAndSortProducts(const vector<Product>& products, double min, double max, const string& output_filename) {
    vector<Product> filteredProducts;

    // Filter products within the price range
    for (size_t i = 0; i < products.size(); ++i) {
        const Product& product = products[i];
        if (product.price >= min && product.price <= max) {
            filteredProducts.push_back(product);
        }
    }

    // Sort filtered products based on the specified criteria
    sort(filteredProducts.begin(), filteredProducts.end(), [](const Product& a, const Product& b) {
        // Sort by rating in descending order
        if (a.average_rating != b.average_rating) {
            return a.average_rating > b.average_rating;
        }
        // If ratings are equal, sort by price in ascending order
        if (a.price != b.price) {
            return a.price < b.price;
        }
        // If prices are equal, sort by title in ascending order
        return a.title < b.title;
    });

    ofstream output_File(output_filename);
    if (!output_File.is_open()) {
        cerr << "Error: Unable to open output file " << output_filename << endl;
    }

    // Print the ordered data into output file
    for (int i = 0; i < filteredProducts.size(); ++i) {
        output_File << filteredProducts[i].title << endl;; 
        output_File << filteredProducts[i].average_rating << endl;
        output_File << filteredProducts[i].rating_number << endl;
        output_File << filteredProducts[i].url << endl;
        output_File << "$" << filteredProducts[i].price << endl;
    }
}

int main(int argc, char *argv[]) {
    // Check if the required number of command-line arguments is provided
    if (argc < 5) {
        cout << "Usage: argument count < 5" << endl;
        exit(1);
    }

    string jsonSource = std::string(argv[1]);
    vector<Product> products = extractDataFromJson(jsonSource);

    string output_filename = std::string(argv[2]);

    double min = stod(argv[3]);
    double max = stod(argv[4]);


    filterAndSortProducts(products, min, max, output_filename);

    return 0;
}
