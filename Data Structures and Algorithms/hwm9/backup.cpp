#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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
        cerr << "Error: Unable to open file " << filePath << endl;
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
            else {
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

const int MAX_PRODUCTS_PER_NODE = 20; // Maximum number of products in a leaf node

class BPlusTreeNode {
public:
    vector<Product> products;
    vector<BPlusTreeNode*> children;
    bool isLeaf;

    BPlusTreeNode(bool leaf) : isLeaf(leaf) {}
};

void insertProduct(BPlusTreeNode* node, const Product& product);
void splitNode(BPlusTreeNode* node);
void traverseBPlusTree(BPlusTreeNode* node, vector<Product>& sortedProducts, double min, double max);
void writeToFile(const vector<Product>& products, const string& filename);
void deleteBPlusTree(BPlusTreeNode* node);

void filterAndSortProducts(const vector<Product>& products, double min, double max, const string& output_filename) {
    BPlusTreeNode* root = new BPlusTreeNode(true);

    for (size_t i = 0; i < products.size(); ++i) {
        const Product& product = products[i];
        if (product.price >= min && product.price <= max) {
            insertProduct(root, product);
        }
    }

    vector<Product> sortedProducts;
    traverseBPlusTree(root, sortedProducts, min, max);
    writeToFile(sortedProducts, output_filename);

    deleteBPlusTree(root);
}


void insertProduct(BPlusTreeNode* node, const Product& product) {
    if (node->isLeaf) {
        vector<Product>::iterator it = lower_bound(node->products.begin(), node->products.end(), product, [](const Product& a, const Product& b) {
            if (a.average_rating != b.average_rating) {
                return a.average_rating > b.average_rating;
            }
            if (a.price != b.price) {
                return a.price < b.price;
            }
            return a.title < b.title;
        });
        node->products.insert(it, product);
        if (node->products.size() > 20) {
            splitNode(node);
        }
    }
    else {
        size_t i = 0;
        while (i < node->products.size() && product.price > node->products[i].price) {
            ++i;
        }
        insertProduct(node->children[i], product);
    }
}

void splitNode(BPlusTreeNode* node) {
    if (node->products.size() <= MAX_PRODUCTS_PER_NODE) {
        return;
    }

    // Create a new child node
    BPlusTreeNode* newChild = new BPlusTreeNode(node->isLeaf);

    // Calculate the index where we split the products
    size_t half = node->products.size() / 2;

    // Move the second half of products to the new child node
    newChild->products.assign(node->products.begin() + half, node->products.end());
    node->products.resize(half); // Resize the current node to keep only the first half

    // If the current node is not a leaf, we need to move children nodes as well
    if (!node->isLeaf) {
        newChild->children.assign(node->children.begin() + half, node->children.end());
        node->children.resize(half); // Resize the current node's children
    }

    // If the current node is a leaf, the new child node should point to the next node
    if (node->isLeaf) {
        newChild->children.push_back(node->children.back());
        node->children.back() = newChild;
    }

    // Find the appropriate parent node for the new child node
    BPlusTreeNode* parent = node->isLeaf ? node : new BPlusTreeNode(false);
    parent->products.push_back(newChild->products.front()); // Update the parent with the new separator
    parent->children.push_back(newChild);

    // Update the node reference
    node = parent;
}


void traverseBPlusTree(BPlusTreeNode* node, vector<Product>& sortedProducts, double min, double max) {
    if (node == nullptr) {
        return;
    }

    if (node->isLeaf) {
        // If leaf node, add all products meeting the criteria to sortedProducts
        for (size_t i = 0; i < node->products.size(); ++i) {
            const Product& product = node->products[i];
            if (product.price >= min && product.price <= max) {
                sortedProducts.push_back(product);
            }
        }
    } else {
        // Traverse children recursively
        for (size_t i = 0; i < node->children.size(); ++i) {
            traverseBPlusTree(node->children[i], sortedProducts, min, max);
        }
    }
}

void writeToFile(const vector<Product>& products, const string& filename) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    for (size_t i = 0; i < products.size(); ++i) {
        outputFile << products[i].title << endl;
        outputFile << products[i].average_rating << endl;
        outputFile << products[i].rating_number << endl;
        outputFile << products[i].url << endl;
        outputFile << "$" << products[i].price << endl;
    }

    outputFile.close();
}

void deleteBPlusTree(BPlusTreeNode* node) {
    if (node == nullptr) {
        return;
    }

    if (!node->isLeaf) {
        for (size_t i = 0; i < node->children.size(); ++i) {
            deleteBPlusTree(node->children[i]);
        }
    }

    delete node;
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "Usage: argument count < 5" << endl;
        exit(1);
    }

    string jsonSource = std::string(argv[1]);
    vector<Product> products = extractDataFromJson(jsonSource); // You need to populate this vector by calling extractDataFromJson
    string output_filename = std::string(argv[2]);
    double min = stod(argv[3]);
    double max = stod(argv[4]);

    filterAndSortProducts(products, min, max, output_filename);

    return 0;
}
