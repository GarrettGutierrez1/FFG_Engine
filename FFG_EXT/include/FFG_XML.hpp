#ifndef FFG_EXT_XML_H_INCLUDED
#define FFG_EXT_XML_H_INCLUDED

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <vector>

/***************************************************************************//**
 * A class that represents an XML tag.
 * 
 * Example usage:
 * -----------------------------------------------------------------------------
 * TODO: Add example usage.
 * -----------------------------------------------------------------------------
 ******************************************************************************/
class FFG_XML_Tag {
public:
    /***************************************************************************//**
	 * The index of this tag's parent.
	 ******************************************************************************/
    int parent;
    /***************************************************************************//**
	 * The index of this tag's first child.
	 ******************************************************************************/
    int first_child;
    /***************************************************************************//**
	 * The number of children this tag has.
	 ******************************************************************************/
    int num_children;
    /***************************************************************************//**
	 * The name of this tag.
	 ******************************************************************************/
    std::string name;
    /***************************************************************************//**
	 * The inner text of this tag.
	 ******************************************************************************/
    std::string inner_text;
    /***************************************************************************//**
	 * The attributes of this tag.
	 ******************************************************************************/
    std::vector<std::pair<std::string, std::string>> attributes;
public:
    FFG_XML_Tag();
    std::string get_attribute(const std::string& attribute_name, const std::string& default_value);
};

/***************************************************************************//**
 * A class for parsing XML documents. A thin wrapper over boost's property_tree.
 * 
 * Example usage:
 * -----------------------------------------------------------------------------
 * TODO: Add example usage.
 * -----------------------------------------------------------------------------
 ******************************************************************************/
class FFG_XML {
public:
    /***************************************************************************//**
	 * The tags of the parsed XML document.
	 ******************************************************************************/
    std::vector<FFG_XML_Tag> tags;
private:
    bool is_tag(const std::string& name);
    void parse_tree(const boost::property_tree::ptree& tree, int parent_index);
public:
    void parse(const std::string filepath);
};

#endif // FFG_EXT_XML_H_INCLUDED
