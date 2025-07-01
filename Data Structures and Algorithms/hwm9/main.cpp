#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Class definition for Product
class Product {
public:
    string main_category;   // Main category of the product
    string title;           // Title of the product
    double average_rating;  // Average rating of the product
    int rating_number;      // Number of ratings received by the product
    double price;           // Price of the product
    string url;             // URL of the product
};


// Function to extract product data from a JSON file
vector<Product> getData(const string& filePath) {
    vector<Product> products; // Initialize an empty vector to store products

    ifstream file(filePath); // Open the JSON file
    // Check if the file is successfully opened
    if (!file.is_open()) {
        cerr << "Error: Unable to open json file " << filePath << endl; 
        return products; 
    }

    string line; // Variable to store each line of the file
    // Read each line of the file until the end is reached
    while (getline(file, line)) {
        Product product; // Create a Product object to store data for each product

        // Find main_category in the line
        size_t main_category_pos = line.find("\"main_category\": \"");
        if (main_category_pos != string::npos) {
            main_category_pos += 18; // Length of "\"main_category\": \""
            size_t end_quote = line.find("\"", main_category_pos);
            // Extract and store main_category information for the product
            product.main_category = line.substr(main_category_pos, end_quote - main_category_pos);
        }

        // Find title in the line
        size_t title_pos = line.find("\"title\": \"");
        if (title_pos != string::npos) {
            title_pos += 10; // Length of "\"title\": \""
            size_t end_quote = line.find("\",", title_pos);
            // Extract and store title information for the product
            product.title = line.substr(title_pos, end_quote - title_pos);
        }

        // Find average_rating in the line
        size_t rating_pos = line.find("\"average_rating\": ");
        if (rating_pos != string::npos) {
            rating_pos += 18; // Length of "\"average_rating\": "
            size_t end_value = line.find(",", rating_pos);
            string rating_str = line.substr(rating_pos, end_value - rating_pos);
            // Convert and store average_rating information for the product
            product.average_rating = stod(rating_str);
        }

        // Find rating_number in the line
        size_t num_pos = line.find("\"rating_number\": ");
        if (num_pos != string::npos) {
            num_pos += 16; // Length of "\"rating_number\": "
            size_t end_value = line.find(",", num_pos);
            string num_str = line.substr(num_pos, end_value - num_pos);
            // Convert and store rating_number information for the product
            product.rating_number = stoi(num_str);
        }

        // Find price in the line
        size_t price_pos = line.find("\"price\": ");
        if (price_pos != string::npos) {
            price_pos += 9; // Length of "\"price\": "
            size_t end_value = line.find(",", price_pos);
            string price_str = line.substr(price_pos, end_value - price_pos);
            // Check if the price is not null, then convert and store price information for the product
            if (price_str != "null") {
                product.price = stod(price_str);
            }
            else {
                product.price = -1; // Set price to -1 if it's null
            }
        }

        // Find URL in the line
        size_t url_pos = line.find("\"thumb\": \"");
        if (url_pos != string::npos) {
            url_pos += 10; // Length of "\"thumb\": \""
            size_t end_quote = line.find("\"", url_pos);
            // Extract and store URL information for the product
            product.url = line.substr(url_pos, end_quote - url_pos);
        }

        products.push_back(product); // Add the extracted product to the vector of products
    }

    file.close(); // Close the file after reading

    return products; // Return the vector containing all the extracted products
}



// Class representing a node in the B+ tree
class TreeNode {
public:
    vector<Product> products; // Vector to store products in the node
    vector<TreeNode*> children; // Vector to store child nodes
    bool isLeaf; // Flag to indicate if the node is a leaf

    // Constructor to initialize the node with the given leaf status
    TreeNode(bool leaf) : isLeaf(leaf) {}
};

// Function declarations
void insertion(TreeNode* node, const Product& product); // Function to insert a product into the B+ tree
void splitNode(TreeNode* node); // Function to split a node if it exceeds the maximum capacity
void parsingTree(TreeNode* node, vector<Product>& sortedProducts, double min, double max); // Function to traverse the B+ tree and collect products within a price range
void PRData(const vector<Product>& products, const string& filename); // Function to write products to a file
void deleteTree(TreeNode* node); // Function to delete the B+ tree
void sorting(const vector<Product>& products, double min, double max, const string& output_filename); // Function to filter and sort products within a price range


// Function to filter and sort products within a specified price range and write them to a file
void sorting(const vector<Product>& products, double min, double max, const string& output_filename) {
    // Create a new root node for the B+ tree
    TreeNode* root = new TreeNode(true);

    // Iterate through each product in the input vector
    for (size_t i = 0; i < products.size(); ++i) {
        const Product& product = products[i];
        // Check if the product's price falls within the specified range
        if (product.price >= min && product.price <= max) {
            // Insert the product into the B+ tree
            insertion(root, product);
        }
    }

    // Vector to store sorted products within the price range
    vector<Product> sortedProducts;
    // Traverse the B+ tree and collect products within the specified price range
    parsingTree(root, sortedProducts, min, max);
    // Write the sorted products to the output file
    PRData(sortedProducts, output_filename);

    // Delete the B+ tree to free memory
    deleteTree(root);
}

// Function to insert a product into a B+ tree node
void insertion(TreeNode* node, const Product& product) {
    // Check if the node is a leaf node
    if (node->isLeaf) {
        // Find the correct position to insert the product in the sorted vector of products
        vector<Product>::iterator it = lower_bound(node->products.begin(), node->products.end(), product, [](const Product& a, const Product& b) {
            // Compare products based on average rating, price, and title
            if (a.average_rating != b.average_rating) {
                return a.average_rating > b.average_rating; // Sort by descending average rating
            }
            if (a.price != b.price) {
                return a.price < b.price; // Sort by ascending price
            }
            return a.title < b.title; // Sort by ascending title
        });
        // Insert the product into the correct position in the node's products vector
        node->products.insert(it, product);
    }
    else {
        // If the node is not a leaf, find the child node to insert the product recursively
        size_t i = 0;
        while (i < node->products.size() && product.price > node->products[i].price) {
            ++i;
        }
        // Recursively insert the product into the appropriate child node
        insertion(node->children[i], product);
    }
}

// Function to traverse a B+ tree and collect products that meet the given criteria
void parsingTree(TreeNode* node, vector<Product>& sortedProducts, double min, double max) {
    // Base case: If the node is nullptr, return
    if (node == nullptr) {
        return;
    }

    // Check if the node is a leaf node
    if (node->isLeaf) {
        // If leaf node, add all products meeting the criteria to sortedProducts
        for (size_t i = 0; i < node->products.size(); ++i) {
            const Product& product = node->products[i];
            // Check if the product's price falls within the given range
            if (product.price >= min && product.price <= max) {
                // If the product meets the criteria, add it to sortedProducts
                sortedProducts.push_back(product);
            }
        }
    } else {
        // If the node is not a leaf, traverse its children recursively
        for (size_t i = 0; i < node->children.size(); ++i) {
            // Traverse each child node recursively, passing the same criteria and sortedProducts vector
            parsingTree(node->children[i], sortedProducts, min, max);
        }
    }
}

// Function to write product data to a file
void PRData(const vector<Product>& products, const string& filename) {
    // Open the output file
    ofstream outputFile(filename);
    // Check if the file is successfully opened
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open output file " << filename << endl;
        return;
    }

    // Iterate through each product in the vector
    for (size_t i = 0; i < products.size(); ++i) {
        // Write each product's information to the output file
        outputFile << products[i].title << endl;
        outputFile << products[i].average_rating << endl;
        outputFile << products[i].rating_number << endl;
        outputFile << products[i].url << endl;
        outputFile << "$" << products[i].price << endl;
    }

    // Close the output file
    outputFile.close();
}

// Function to delete the B+ tree recursively
void deleteTree(TreeNode* node) {
    // Check if the node is nullptr (base case for recursion)
    if (node == nullptr) {
        return; // If so, return without further action
    }

    // Check if the node is not a leaf node
    if (!node->isLeaf) {
        // If it's not a leaf node, iterate through its children
        for (size_t i = 0; i < node->children.size(); ++i) {
            // Recursively call deleteTree for each child node
            deleteTree(node->children[i]);
        }
    }

    // Delete the current node
    delete node;
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "Usage: argument count < 5" << endl;
        exit(1);
    }

    string jsonSource = std::string(argv[1]);
    vector<Product> products = getData(jsonSource);
    string output_filename = std::string(argv[2]);
    double min = stod(argv[3]);
    double max = stod(argv[4]);

    sorting(products, min, max, output_filename);

    return 0;
}
