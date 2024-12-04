#include <iostream>
#include "link.h"

// Constructor
Link::Link(char n, char t, int s, 
bool reveal, bool is_downloaded, bool linkboost, bool protect, bool brutal) 
    : name{n}, type{t}, strength{s}, reveal{reveal}, downloaded{is_downloaded}, linkboost{linkboost},
    protect{protect}, brutal{brutal} {
    if ((n < 'a' || n > 'h') && (n < 'A' || n > 'H')) {
        throw std::invalid_argument("Invalid link name. Must be 'a'-'h' or 'A'-'H'.");
    }
    if (t != 'D' && t != 'V') {
        throw std::invalid_argument("Invalid link type. Must be 'D' or 'V'.");
    }
    if (s < 0) {
        throw std::invalid_argument("Strength must be non-negative.");
    }
}

// the big 5

Link::Link(const Link& other): 
name{other.name}, type{other.type}, strength{other.strength}, 
reveal{other.reveal}, downloaded{other.downloaded}, linkboost{other.linkboost}{}

Link& Link::operator=(const Link& other){
    if (this == &other) return *this;
    Link tmp(other);
    std::swap(*this, tmp);
    return *this;
}

Link::Link(Link&& other) noexcept
    : name{other.name}, 
      type{other.type}, 
      strength{other.strength}, 
      reveal{other.reveal}, 
      downloaded{other.downloaded}, 
      linkboost{other.linkboost} {

    std::cout << "Moving Link: " << name << std::endl; 
    
    // Reset the other object's members to their default values
    other.name = '\0';
    other.type = '\0';
    other.strength = 0;
    other.reveal = false;
    other.downloaded = false;
    other.linkboost = false;
}

Link& Link::operator=(Link&& other) noexcept {
    if (this != &other) { // Self-assignment check
        // Swap the member variables with the other object
        std::swap(name, other.name);
        std::swap(type, other.type);
        std::swap(strength, other.strength);
        std::swap(reveal, other.reveal);
        std::swap(downloaded, other.downloaded);
        std::swap(linkboost, other.linkboost);
    }
    return *this; // Return the current object
}

// Setters
void Link::set_name(char c) {name = c;}
void Link::set_revealed(bool b) {reveal = b;}
void Link::set_downloaded(bool b) {downloaded = b;}
void Link::set_type(char new_type) {type = new_type;}
void Link::set_linkboost() {linkboost = true;}
void Link::set_protection() {protect = true;}
void Link::set_brutal() {brutal = true;}


// Getters
int Link::get_player() const {return (name >= 'a' && name <= 'h') ? 1 : 2;}
char Link::get_name() const { return name; }
char Link::get_type() const { return type; }
int Link::get_strength() const { return strength; }
std::string Link::get_info() const {
    return reveal ? std::string(1, type) + std::to_string(strength) : "?";
}
std::string Link::get_full_info() const {
    return std::string(1, type) + std::to_string(strength);
}

// Other member functions
bool Link::is_revealed() const {return reveal;}
bool Link::is_downloaded() const { return downloaded; }
bool Link::is_linkboost() const {return linkboost;}
bool Link::is_protected() const {return protect;}
bool Link::is_brutal() const {return brutal;}

