/* 
 * File:   vendor.hpp
 * Author: Brandan Tyler Lasley
 *
 * Created on November 15, 2014, 10:51 AM
 */
#ifdef _MSC_VER // Disables Microsofts Cross-platform restriction warning. 
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef VENDOR_HPP
#define	VENDOR_HPP
#include <string.h>
#include <stdexcept>

class vendor {
public:
    vendor();
    vendor(const vendor& obj);
    virtual ~vendor();

    void setName(const char * _name);
    void setProduct(const char * _product);
    void setEvent(const char * _event);
    void setPhone(const char * _phone);


    char * getName() const;
    char * getProduct() const;
    char * getEvent() const;
    char * getPhone() const;

    bool operator==(const vendor& obj) const;
    const vendor& operator=(const vendor& obj);
    bool operator<(const vendor& obj) const;
private:
    char * name;
    char * product;
    char * event;
    char * phone;
};

#endif	/* VENDOR_HPP */