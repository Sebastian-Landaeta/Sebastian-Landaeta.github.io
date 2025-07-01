#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;


class Comment {
private: // initiate values
    std::string video_id;
    std::string author;
    std::string comment_id;
    int like_count;
    int reply_count;
    bool is_reply;
    std::string parent_comment_id;
    std::string published_date;
    std::string crawled_date;
    bool is_video_owner;
    std::string comment;

public:
    // Constructor that takes a JSON string and initializes the object
    Comment(const std::string& jsonStr) {
        // You may use a JSON parsing library to parse the string,
        // but for simplicity, let's assume a simple parsing method here.
        std::map<std::string, std::string> jsonMap;

        // Parsing the JSON string (simplified version)
        size_t pos = 1; // Skip the initial '{'
        while (pos < jsonStr.length() - 1) { // -1 to skip the final '}'
            // Find the key
            size_t keyStart = jsonStr.find_first_of('"', pos) + 1;
            size_t keyEnd = jsonStr.find_first_of('"', keyStart);
            std::string key = jsonStr.substr(keyStart, keyEnd - keyStart);

            if (key == "video_id"){ // statement to find each individual sub section by getting a key and comparing it to the options
                size_t valueStart = jsonStr.find_first_of('"', keyEnd + 2) + 1;
                size_t valueEnd = jsonStr.find_first_of('"', valueStart);
                std::string value = jsonStr.substr(valueStart, valueEnd - valueStart);

                jsonMap[key] = value;

                // Move to the next key
                pos = valueEnd + 2; // Skip the comma and space
            }
            else if (key == "author"){ // locate and save  author sector
                size_t valueStart = jsonStr.find_first_of('"', keyEnd + 2) + 1;
                size_t valueEnd = jsonStr.find_first_of('"', valueStart);
                std::string value = jsonStr.substr(valueStart, valueEnd - valueStart);

                jsonMap[key] = value;

                // Move to the next key
                pos = valueEnd + 2; // Skip the comma and space
            }
            else if (key == "comment_id"){ // locate and save  the comment ID
                size_t valueStart = jsonStr.find_first_of('"', keyEnd + 2) + 1;
                size_t valueEnd = jsonStr.find_first_of('"', valueStart);
                std::string value = jsonStr.substr(valueStart, valueEnd - valueStart);

                jsonMap[key] = value;

                // Move to the next key
                pos = valueEnd + 2; // Skip the comma and space
            }
            else if (key == "like_count"){ // locate  and save the like count
                size_t valueStart = jsonStr.find_first_of(": ", keyEnd + 2) + 1;
                size_t valueEnd = jsonStr.find_first_of(',', valueStart);
                std::string value = jsonStr.substr(valueStart, valueEnd - valueStart);

                jsonMap[key] = value;

                // Move to the next key
                pos = valueEnd + 2; // Skip the comma and space
            }
            else if (key == "reply_count"){ // locate  and save the reply count
                size_t valueStart = jsonStr.find_first_of(": ", keyEnd + 2) + 1;
                size_t valueEnd = jsonStr.find_first_of(',', valueStart);
                std::string value = jsonStr.substr(valueStart, valueEnd - valueStart);

                jsonMap[key] = value;

                // Move to the next key
                pos = valueEnd + 2; // Skip the comma and space
            }
            else if (key == "is_reply"){ // locate  and save the is reply statement
                size_t valueStart = jsonStr.find_first_of(": ", keyEnd + 2) + 1;
                size_t valueEnd = jsonStr.find_first_of(',', valueStart);
                std::string value = jsonStr.substr(valueStart, valueEnd - valueStart);

                jsonMap[key] = value;

                // Move to the next key
                pos = valueEnd + 2; // Skip the comma and space
            }
            else if (key == "parent_comment_id"){ // locate and save the parent ID
                size_t valueStart = jsonStr.find_first_of('"', keyEnd + 2) + 1;
                size_t valueEnd = jsonStr.find_first_of('"', valueStart);
                std::string value = jsonStr.substr(valueStart, valueEnd - valueStart);

                jsonMap[key] = value;

                // Move to the next key
                pos = valueEnd + 2; // Skip the comma and space
            }
            else if (key == "published_date"){ // locate and save published date
                size_t valueStart = jsonStr.find_first_of('"', keyEnd + 2) + 1;
                size_t valueEnd = jsonStr.find_first_of('"', valueStart);
                std::string value = jsonStr.substr(valueStart, valueEnd - valueStart);

                jsonMap[key] = value;

                // Move to the next key
                pos = valueEnd + 2; // Skip the comma and space
            }
            else if (key == "crawled_date"){ // locate and save crawled date
                size_t valueStart = jsonStr.find_first_of('"', keyEnd + 2) + 1;
                size_t valueEnd = jsonStr.find_first_of('"', valueStart);
                std::string value = jsonStr.substr(valueStart, valueEnd - valueStart);

                jsonMap[key] = value;

                // Move to the next key
                pos = valueEnd + 2; // Skip the comma and space
            }
            else if (key == "is_video_owner"){ // locate and save video owner statement
                size_t valueStart = jsonStr.find_first_of(": ", keyEnd + 2) + 1;
                size_t valueEnd = jsonStr.find_first_of(',', valueStart);
                std::string value = jsonStr.substr(valueStart, valueEnd - valueStart);

                jsonMap[key] = value;

                // Move to the next key
                pos = valueEnd + 2; // Skip the comma and space
            }
            else if (key == "comment"){ // locate and save comment
                size_t valueStart = jsonStr.find_first_of('"', keyEnd + 2) + 1;
                size_t valueEnd = jsonStr.find_first_of('"', valueStart);
                std::string value = jsonStr.substr(valueStart, valueEnd - valueStart);

                jsonMap[key] = value;

                // Move to the next key
                pos = valueEnd + 2; // Skip the comma and space
            }

        }

        // Assign values to class members
        video_id = jsonMap["video_id"];
        author = jsonMap["author"];
        comment_id = jsonMap["comment_id"];
        like_count = stoi(jsonMap["like_count"]);
        reply_count = stoi(jsonMap["reply_count"]);
        is_reply = (jsonMap["is_reply"] == "true");
        parent_comment_id = jsonMap["parent_comment_id"];
        published_date = jsonMap["published_date"];
        crawled_date = jsonMap["crawled_date"];
        is_video_owner = (jsonMap["is_video_owner"] == "true");
        comment = jsonMap["comment"];
    }

    void print() const { //debugging class print
        cout << "Video ID: " << video_id << std::endl;
        cout << "Author: " << author << std::endl;
        cout << "Comment ID: " << comment_id << std::endl;
        cout << "Like Count: " << like_count << std::endl;
        cout << "Reply Count: " << reply_count << std::endl;
        cout << "Is Reply: " << (is_reply ? "true" : "false") << std::endl;
        cout << "Parent Comment ID: " << parent_comment_id << std::endl;
        cout << "Published Date: " << published_date << std::endl;
        cout << "Crawled Date: " << crawled_date << std::endl;
        cout << "Is Video Owner: " << (is_video_owner ? "true" : "false") << std::endl;
        cout << "Comment: " << comment << std::endl;
    }
    //getters 
    std::string getCommentId() const {
        return comment_id;
    }

    std::string getlike_count() const {
        return to_string(like_count);
    }

    std::string getreply_count() const {
        return to_string(reply_count);
    }

    std::string getAuthor() const {
        return author;
    }

    std::string getParentCommentId() const {
        return parent_comment_id;
    }

    std::string getVideo_Id() const {
        return video_id;
    }

    std::string getPublishedDate() const {
        return published_date;
    }

    std::string getComment() const {
        return comment;
    }
    //setters
    void plusLike(){
        ++like_count;
    }

    void plusComment(){
        ++reply_count;
    }
    
    void removeParent(){
        parent_comment_id = "";
    }

    void resetReply(){
        reply_count = 0;
    }
};

// Define TreeNode class
class TreeNode {
public:
    Comment data;
    std::vector<TreeNode*> children;

    // Constructor
    TreeNode(const Comment& comment) : data(comment) {}
};

// Define buildTree function
void buildTree(const std::vector<Comment>& comments, std::map<std::string, TreeNode*>& commentMap) {
    // Create TreeNodes for all comments and store them in commentMap
    for (size_t i = 0; i < comments.size(); ++i) {
        TreeNode* node = new TreeNode(comments[i]);
        commentMap[comments[i].getCommentId()] = node;
    }

    // Link child comments to their parent comments
    for (size_t i = 0; i < comments.size(); ++i) {
        const std::string& parentCommentId = comments[i].getParentCommentId();
        if (!parentCommentId.empty()) {
            std::map<std::string, TreeNode*>::iterator parentNodeIterator = commentMap.find(parentCommentId);
            if (parentNodeIterator != commentMap.end()) {
                TreeNode* parentNode = parentNodeIterator->second;
                if (parentNode != nullptr) {
                    parentNode->children.push_back(commentMap[comments[i].getCommentId()]);
                }
            }
        } else {
            // If a comment has no parent comment ID, it's a root node
            // Add it directly to the commentMap with its own ID
            if (commentMap.find(comments[i].getCommentId()) == commentMap.end()) {
                TreeNode* rootNode = commentMap[comments[i].getCommentId()];
                commentMap[comments[i].getCommentId()] = rootNode;
            }
        }
    }
}

// Define printTree function
void printTree(TreeNode* root, std::ostream& output, int depth = 0) {
    if (root != nullptr) {
        // Print the current node's data with appropriate indentation
        string indent = "";
        for (int i = 0; i < depth; ++i){
            indent = indent + "    "; // Indentation based on depth
        }
        // Print the comment details
        output << indent << root->data.getAuthor() << " " << root->data.getPublishedDate();
        if (depth == 0){
            output << endl;
        }
        else{
            output << endl;
        }
        output << indent << root->data.getComment() << std::endl;
        output << indent << "\U0001F44D " << root->data.getlike_count() << std::endl;
        if ( root->data.getreply_count() != "0"  && root->data.getreply_count() != "1" ){ // if multiple comments use replies 
            output << indent << root->data.getreply_count() << " replies" << std::endl;
        }
        else if ( root->data.getreply_count() != "0" && root->data.getreply_count() == "1" ){ // if one comment use reply
            output << indent << root->data.getreply_count() << " reply" << std::endl;
        }
        // Recursively print the children with increased indentation
        for (size_t i = 0; i < root->children.size(); ++i) {
            printTree(root->children[i], output, depth + 1);
        }
    }
}

//helper function to detect command
bool containsSubstring(const std::string& str, const std::string& substr) {
    return str.find(substr) != std::string::npos;
}

// helper function to devide the command data
void divideStringReplyComment(const std::string& line, std::string& command, std::string& parentID, std::string& ID, std::string& user, std::string& comment) {
    std::istringstream iss(line);

    // Extracting components
    iss >> command >> parentID >> ID >> user;

    // Extracting comment (including spaces)
    std::getline(iss >> std::ws, comment);

    // Removing leading and trailing quotes from comment
    comment = comment.substr(1, comment.size() - 2);
}

// helper function to devide the command data
void divideStringReplyVideo(const std::string& line, std::string& command, std::string& ID, std::string& user, std::string& comment) {
    std::istringstream iss(line);

    // Extracting components
    iss >> command >> ID >> user;

    // Extracting comment (including spaces)
    std::getline(iss >> std::ws, comment);

    // Removing leading and trailing quotes from comment
    comment = comment.substr(1, comment.size() - 2);
}

// helper function to devide the command data
void divideStringLikeComment(const std::string& line, std::string& command, std::string& ID) {
    std::istringstream iss(line);

    // Extracting components
    iss >> command >> ID;
}

// helper function to devide the command data
void divideStringDeleteComment(const std::string& line, std::string& command, std::string& ID) {
    std::istringstream iss(line);

    // Extracting components
    iss >> command >> ID;
}

// helper function to devide the command data
void divideStringPRComment(const std::string& line, std::string& command, std::string& ID) {
    std::istringstream iss(line);

    // Extracting components
    iss >> command >> ID;
}

vector<Comment> reply_video(std::vector<Comment> comments, const string& ID, const string& user, const string& commentadd, const string& video_id){
    string line = "{\"video_id\": \"" + video_id + "\", \"author\": \"" + user + "\", \"comment_id\": \"" + ID + "\", \"like_count\": 0, \"reply_count\": 0, \
    \"is_reply\": false, \"parent_comment_id\": \"\", \"published_date\": \"0 seconds ago\", \"crawled_date\": \"\", \"is_video_owner\": , \"comment\": \"" + commentadd + "\"}";
    Comment comment(line); // add to class
    comments.push_back(comment); // add to storage
    return comments;
}

vector<Comment> reply_comment(std::vector<Comment> comments, const string& parentID, const string& ID, const string& user, const string& commentadd, const string& video_id){
    string line = "{\"video_id\": \"" + video_id + "\", \"author\": \"" + user + "\", \"comment_id\": \"" + ID + "\", \"like_count\": 0, \"reply_count\": 0, \
    \"is_reply\": true, \"parent_comment_id\": \"" + parentID + "\", \"published_date\": \"0 seconds ago\", \"crawled_date\": \"\", \"is_video_owner\": , \"comment\": \"" + commentadd + "\"}";
    Comment comment(line); // add to class
    comments.push_back(comment); // add to storage
    for (size_t i = 0; i < comments.size(); ++i) {
        if (comments[i].getCommentId() == parentID) {
            comments[i].plusComment(); // update comment count
            break;
        }
    }
    return comments;
}

vector<Comment> like_comment(std::vector<Comment> comments, const string& ID){
    for (size_t i = 0; i < comments.size(); ++i) {
        if (comments[i].getCommentId() == ID) {
            comments[i].plusLike(); // update like count
            return comments;
        }
    }
    return comments;
}

vector<Comment> delete_comment(std::vector<Comment> comments, const string& ID){
    // Iterate through the vector and erase the element with the specific comment_id
    for (std::vector<Comment>::iterator it = comments.begin(); it != comments.end(); ++it) {
        if (it->getCommentId() == ID) { // find target comment
            string repliedComment = it->getParentCommentId();
            comments.erase(it); // delete it
            for (std::vector<Comment>::iterator it2 = comments.begin(); it2 != comments.end(); ++it2) {
                if (it2->getCommentId() == repliedComment) { // find replied comment and set its replyes to 0
                    it2->resetReply();
                }
            }
        }
    }
    for (std::vector<Comment>::iterator it = comments.begin(); it != comments.end(); ++it) {
        if (it->getParentCommentId() == ID) { // find any comments that had the comment as parent and unlink them
            it->removeParent();

        }
    }
    return comments;
}

void printComment(std::vector<Comment> comments, const string& ID, ofstream& output_file){

    // Build the tree based on parent comment IDs
    map<string, TreeNode*> commentMap;
    buildTree(comments, commentMap);

    // Print the tree
    for (size_t i = 0; i < comments.size(); ++i) {
        if (comments[i].getCommentId() == ID) {
            printTree(commentMap[comments[i].getCommentId()], output_file);
        }
    }

    // Inside the printComment function, after using commentMap:
    for (std::map<std::string, TreeNode*>::iterator it = commentMap.begin(); it != commentMap.end(); ++it) {
        delete it->second; // Delete TreeNode objects
    }
    commentMap.clear(); // Clear the map
}

void input_execute(const string& input_filename, std::vector<Comment> comments, const string& video_id, const string& output_filename){
    ifstream input_file(input_filename);
    if (!input_file.is_open()) {
        cerr << "Failed to open the input file." << endl;
        exit(1);
    }

    ofstream output_file(output_filename);
    if (!output_file.is_open()) {
        cerr << "Failed to open the output file." << endl;
        exit(1);
    }

    string line;
    while (getline(input_file, line)) {
        if (containsSubstring(line, "reply_to_video")){ //reply video option catcher
            string command, parentID, ID, user, comment;
            divideStringReplyVideo(line, command, ID, user, comment);
            comments = reply_video(comments, ID, user, comment, video_id);
        }
        else if (containsSubstring(line, "reply_to_comment")){ // reply comment option catcher
            string command, parentID, ID, user, comment;
            divideStringReplyComment(line, command, parentID, ID, user, comment);
            comments = reply_comment(comments, parentID, ID, user, comment, video_id);
        }
        else if (containsSubstring(line, "like_comment")){ // like comment option catcher
            string command, parentID, ID, user, comment;
            divideStringLikeComment(line, command, ID);
            comments = like_comment(comments, ID);
        }
        else if (containsSubstring(line, "delete_comment")){ // delete comment option catcher
            string command, parentID, ID, user, comment;
            divideStringDeleteComment(line, command, ID);
            comments = delete_comment(comments, ID);
        }
        else if (containsSubstring(line, "display_comment")){ // display comment option catcher
            string command, parentID, ID, user, comment;
            divideStringPRComment(line, command, ID);
            printComment(comments, ID, output_file);
        }
    }
    input_file.close();
    output_file.close(); //close files
}

int main(int argc, char *argv[]) {
    // Check if the required number of command-line arguments is provided
    if (argc < 4) {
        cout << "Usage: argument count < 4" << endl;
        exit(1);
    }

    // assume inputFile is a std::string, containing the file name of the input file.
    string jsonSource = std::string(argv[1]);
    std::ifstream jsonFile(jsonSource);
    if (!jsonFile.is_open()) {
            std::cerr << "Failed to open the JSON file." << std::endl;
            exit(1);
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(jsonFile, line)) {
        lines.push_back(line);
    }

    // don't need this json file anymore, as the content is read into json_content.
    jsonFile.close();

    std::vector<Comment> comments;
    for (size_t i = 0; i < lines.size(); ++i) {
        Comment comment(lines[i]);
        comments.push_back(comment);
    }

    string video_id = comments[1].getVideo_Id();

    // Build the tree based on parent comment IDs
    std::map<std::string, TreeNode*> commentMap;
    buildTree(comments, commentMap);

    input_execute(std::string(argv[2]), comments, video_id, std::string(argv[3]));

    // delete inside the printComment function
    for (std::map<std::string, TreeNode*>::iterator it = commentMap.begin(); it != commentMap.end(); ++it) {
        delete it->second; // Delete TreeNode obj
    }
    commentMap.clear(); // Clear the map

    return 0;
}