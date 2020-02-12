#include "FFG_XML.hpp"

/***************************************************************************//**
 * Returns a constant static empty ptree.
 * @return A constant static empty ptree.
 ******************************************************************************/
const boost::property_tree::ptree& empty_ptree() {
    static boost::property_tree::ptree t;
    return t;
}

/***************************************************************************//**
 * Constructor.
 ******************************************************************************/
FFG_XML_Tag::FFG_XML_Tag() {
    parent = -1;
    first_child = -1;
    num_children = 0;
    name = "";
    inner_text = "";
}

/***************************************************************************//**
 * Finds the first attribute of this tag with the same name and returns its
 * value.
 * @param attribute_name The name of the attribue to look for.
 * @param default_value The value to return if no matching attribute was found.
 * @return The value of the attribute if found, otherwise default_value.
 ******************************************************************************/
std::string FFG_XML_Tag::get_attribute(const std::string& attribute_name, const std::string& default_value) {
    for(auto& name_value_pair : attributes) {
        if(attribute_name.compare(name_value_pair.first) == 0) return name_value_pair.second;
    }
    return default_value;
}

/***************************************************************************//**
 * Utility method that identifies by a tree's name if it is a tag.
 * @param name The name of the tree.
 * @return True if it is a tag, otherwise false.
 ******************************************************************************/
bool FFG_XML::is_tag(const std::string& name) {
    if(name.length() < 1) return false;
    if(name.length() == 1) return true;
    if(name[0] == '<' && name[name.length() - 1] == '>') return false;
    return true;
}

/***************************************************************************//**
 * Internal recursive method that iterates over all children of the input tree
 * and looks for XML tags and attributes, editing the tag list as necessary.
 * @param tree The tree to recursively scan.
 * @param parent_index The index of parent of all the children in the tree.
 ******************************************************************************/
void FFG_XML::parse_tree(const boost::property_tree::ptree& tree, int parent_index) {
    int first_child = -1;
    int num_children = 0;
    std::vector<boost::property_tree::ptree> child_trees;
    for(auto& name_tree_pair : tree) {
        const std::string& name = name_tree_pair.first;
        const boost::property_tree::ptree& child_tree = name_tree_pair.second;
        if(is_tag(name)) {
            int child_index = tags.size();
            tags.emplace_back();
            FFG_XML_Tag& child_tag = tags[child_index];
            child_tag.parent = parent_index;
            child_tag.name = name;
            child_tag.inner_text = child_tree.data();
            if(first_child < 0) {
                first_child = child_index;
            }
            num_children++;
            child_trees.push_back(child_tree);
        } else if(name == "<xmlattr>" && parent_index >= 0) {
            FFG_XML_Tag& parent_tag = tags[parent_index];
            for(auto& attr_tree_pair : child_tree) {
                std::pair<std::string, std::string> attr_value_pair(attr_tree_pair.first, attr_tree_pair.second.data());
                parent_tag.attributes.push_back(attr_value_pair);
            }
        }
    }
    if(parent_index >= 0) {
        FFG_XML_Tag& parent_tag = tags[parent_index];
        parent_tag.first_child = first_child;
        parent_tag.num_children = num_children;
    }
    for(int i = 0; i < num_children; i++) {
        parse_tree(child_trees[i], first_child + i);
    }
}

/***************************************************************************//**
 * Parses an XML file and fills out the FFG_XML.
 * @param filepath The path to an .xml file.
 ******************************************************************************/
void FFG_XML::parse(const std::string filepath) {
    tags.resize(0);
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(filepath, tree);
    FFG_XML_Tag document_tag;
    document_tag.name = "document";
    tags.push_back(document_tag);
    parse_tree(tree, 0);
}
