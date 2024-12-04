#ifndef LINK_H
#define LINK_H

#include <string>
#include <stdexcept> // For exceptions

class Link {
    char name;         // a, b, c, ..., A, B, C
    char type;         // 'D' or 'V'
    int strength;
    bool reveal;
    bool downloaded;   // Whether the link has been downloaded
    bool linkboost;     // whether linkboost is applied to this link
    bool protect;
    bool brutal;

public:
    // the big 5

    Link(char n, char t, int s, bool reveal = false, bool is_downloaded = false, bool linkboost = false,
    bool protect = false, bool brutal = false);
    ~Link() = default; // Use the default destructor if no dynamic memory is involved
    Link(const Link& other);                // Copy Constructor
    Link& operator=(const Link& other);     // Copy Assignment Operator
    Link(Link&& other) noexcept;            // Move Constructor
    Link& operator=(Link&& other) noexcept; // Move Assignment Operator

    // Getters
    int get_player() const; // Returns 1 or 2 to indicate the player
    char get_name() const;
    char get_type() const;
    int get_strength() const;
    std::string get_full_info() const;
    std::string get_info() const;


    // Setters
    void set_name(char c);
    void set_revealed(bool b);
    void set_downloaded(bool b);
    void set_type (char new_type);
    void set_linkboost();
    void set_protection();
    void set_brutal();

    // Other member functions
    bool is_revealed() const;
    bool is_downloaded() const;
    bool is_linkboost() const;
    bool is_protected() const;
    bool is_brutal() const ;
};
#endif

