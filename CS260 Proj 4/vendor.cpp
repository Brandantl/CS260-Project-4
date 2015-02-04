/* 
 * File:   vendor.cpp
 * Author: Brandan Tyler Lasley
 * 
 * Created on November 15, 2014, 10:51 AM
 */

#include "vendor.hpp"

vendor::vendor() {
    this->phone = NULL;
    this->name = NULL;
    this->event = NULL;
    this->product = NULL;
}

vendor::vendor(const vendor& obj) {
    this->phone = NULL;
    this->name = NULL;
    this->event = NULL;
    this->product = NULL;
    this->setEvent(obj.getEvent());
    this->setName(obj.getName());
    this->setPhone(obj.getPhone());
    this->setProduct(obj.getProduct());
}

vendor::~vendor() {
    if (this->event) {
        delete [] this->event;
    }
    if (this->name) {
        delete [] this->name;
    }
    if (this->product) {
        delete [] this->product;
    }
    if (this->phone) {
        delete [] this->phone;
    }
    this->phone = 0;
}

void vendor::setName(const char * _name) {
    if (this->name) {
        delete [] this->name;
    }
    if (_name) {
        this->name = new char[strlen(_name) + 1];
        strcpy(this->name, _name);
    } else {
        throw std::invalid_argument("Name CANNOT be NULL"); // FATAL ERROR: We don't know what to do if this occurs!?  We don't want to corrupt collection.cpp
    }
}

void vendor::setProduct(const char * _product) {
    if (this->product) {
        delete [] this->product;
    }
    if (_product) {
        this->product = new char[strlen(_product) + 1];
        strcpy(this->product, _product);
    } else {
        throw std::invalid_argument("Product CANNOT be NULL"); //  FATAL ERROR: We don't know what to do if this occurs!? We don't want to corrupt collection.cpp
    }
}

void vendor::setEvent(const char * _event) {

    if (this->event) {
        delete [] this->event;
    }
    if (_event) {
        this->event = new char[strlen(_event) + 1];
        strcpy(this->event, _event);
    } else {
        this->event = NULL;
    }
}

void vendor::setPhone(const char * _phone) {
    if (this->phone) {
        delete [] this->phone;
    }
    if (_phone) {
        this->phone = new char[strlen(_phone) + 1];
        strcpy(this->phone, _phone);
    } else {
        this->phone = NULL;
    }
}

char * vendor::getName() const {
    if (this->name) {
        return this->name;
    }
    return NULL;
}

char * vendor::getProduct() const {
    if (this->product) {
        return this->product;
    }
    return NULL;
}

char * vendor::getEvent() const {
    if (this->event) {
        return this->event;
    }
    return NULL;
}

char * vendor::getPhone() const {
    if (this->phone) {
        return this->phone;
    }
    return NULL;
}

bool vendor::operator==(const vendor& obj) const {
    if (strcmp(obj.getName(), this->name) == 0) {
        return true;
    }
    return false;
}

const vendor& vendor::operator=(const vendor& obj) {
    if (this == &obj) {
        return *this;
    } else {
        this->phone = NULL;
        this->name = NULL;
        this->event = NULL;
        this->product = NULL;
        this->setEvent(obj.getEvent());
        this->setName(obj.getName());
        this->setPhone(obj.getPhone());
        this->setProduct(obj.getProduct());
        return *this;
    }
}

bool vendor::operator<(const vendor& obj) const {
    if (strcmp(obj.getName(), this->name) < 0) {
        return true;
    } else {
        return false;
    }
}