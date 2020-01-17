/*
 *  Copyright (C) 2019 Ben Kronemeyer - All Rights Reserved
 *  Kronemeb@email.sc.edu
 *
 *  This file was created to demonstrate the Karatsuba Algorithm when compared to
 *  the generic gradeschool algorithm. The algorithm uses integer vectors throughout
 *  so custom vector addition and subtraction had to be implemented.
 * 
 */
#include <algorithm>
using std::transform;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::stoi;
#include <vector>
using std::vector;

vector<int> gradeSchool(vector<int> a, vector<int> b);
vector<int> karatsuba(vector<int> a1, vector<int> b1);
vector<int> add(vector<int> a, vector<int> b);
vector<int> sub(vector<int> a, vector<int> b);
vector<int> freebasing(vector<int> a, int base);
vector<int> lengthcheck(vector<int> first, vector<int> second);

int main() {
    string entry;
    string letter;
    unsigned int i, mult;
    vector<int> first;
    vector<int> second;
    cout << "Enter the numbers to multiply: ";
    cin >> entry;
    mult = entry.find('*');
    // Parse entry into seperate vectors
    for (i = 0; i < mult;i++){
        letter = entry.at(i);
        first.push_back(stoi(letter));
    }
    for (i = mult+1;i<entry.length();i++) {
        letter = entry.at(i);
        second.push_back(stoi(letter));
    }
    // Ensure vectors are same size
    if (first.size() != second.size()) {
        if (first.size()>second.size()){
            second = lengthcheck(first,second);
        } else {first = lengthcheck(first,second);}
    }

    vector<int> kresult, gresult;
    // Get gradeSchool result and Karatsuba result of first vect and second vect
    gresult = gradeSchool(first,second);
    kresult = karatsuba(first, second);
 
    // Remove leading 0's of karatsuba result
    while (kresult.at(0) == 0 && kresult.size() > 1) {
        kresult.erase(kresult.begin());
    }
    // Remove leading 0's of gradeSchool result
    while (gresult.at(0) == 0 && gresult.size() > 1) {
        gresult.erase(gresult.begin());
    }
    cout << endl << "B: ";
    for (i = 0;i<gresult.size();i++) {
        cout << gresult.at(i);
    }
    cout << endl << "K: ";
    for (i = 0;i<kresult.size();i++) {
        cout << kresult.at(i);
    }
		cout << endl;
    return 0;
}

/*
    Gradeschool way to calculate multiplication of two large numbers.
    Trail variable is used to append the trailing 0's when needed for 
    multiples of 10. 
*/
vector<int> gradeSchool(vector<int> a, vector<int> b) {
    vector<int> result, sum;
    int carry = 0, mult, trail = 0;
    for (int i = b.size()-1; i>=0;i--){
        result.insert(result.begin(),trail,0);
        for (int j = a.size()-1; j>=0; j--) {
            mult = b.at(j)*a.at(i) + carry;
            if (mult>10) {
                carry = mult/10;
                result.insert(result.begin(),mult%10);
            } else {
                carry = 0;
                result.insert(result.begin(),mult);
            }
        }
        if (carry!=0) { 
            result.insert(result.begin(),carry);
            carry=0;
				}
        if (sum.size() != result.size()) {
            if (sum.size()>result.size()) {
                result = lengthcheck(sum,result);
            } else {sum = lengthcheck(sum,result);}
        }
        sum = add(sum,result);
        result.clear();
        trail++;
    }
    return sum;
}

/* 
    Recursive function to solve the large integer multiplication 
    Had to continually make sure the sizes of the vectors were 
    multiples of 2 and also of equal length.
*/
vector<int> karatsuba(vector<int> a0, vector<int> b0) {
    vector<int> end;
    if (a0.size()==1) 
			return gradeSchool(a0,b0);
    
    if (a0.size()%2!=0) 
        a0.insert(a0.begin(),0);
    if (b0.size()%2!=0)
        b0.insert(b0.begin(),0);

    int i, mid = (a0.size()/2);
    vector<int> a1, b1, c0, c1, c2, a2, b2;
    for (i=0;i<mid;i++){
        a1.push_back(a0.at(0));
        a0.erase(a0.begin());
        b1.push_back(b0.at(0));
        b0.erase(b0.begin());
    }

    c2 = karatsuba(a1,b1);   
    c0 = karatsuba(a0,b0);

    a2 = add(a1,a0);
    b2 = add(b1,b0);
    if (a2.size() != b2.size()) {
        if (a2.size()>b2.size()){
            b2 = lengthcheck(a2,b2);
        } else {a2 = lengthcheck(a2,b2);}
    }
    c1 = karatsuba(a2,b2);
    c1 = sub(c1,c2);
    c1 = sub(c1,c0);
    c2 = freebasing(c2,mid*2);
    c1 = freebasing(c1,mid);
    end = add(c2,c1);
    end = add(end,c0);
    return end;
}

/*
    Add's two vectors together keeping track of carry's (only works for base 10 numbers)
*/
vector<int> add(vector<int> a, vector<int> b) {
    vector<int> result;
    int carry = 0, add = 0;
    if (a.size() != b.size()) {
        if (a.size()>b.size()){
            b = lengthcheck(a,b);
        } else {a = lengthcheck(a,b);}
    }
    for (int i=a.size()-1;i>=0;i--) {
        add = a[i]+b[i]+carry;
        if (add>=10) {
            add -= 10;
            carry = 1;
            result.insert(result.begin(),add);
        } else {
            carry = 0;
            result.insert(result.begin(),add);
        }
    }
    if (carry == 1) {
        result.insert(result.begin(),carry);
    }
    return result;
}

/*
    Subtracts two vectors, keeping track of carries (only works for base 10 numbers)
*/
vector<int> sub(vector<int> left, vector<int> right){
    vector<int> result;
    int carry = 0, sub = 0;
    if (left.size() != right.size()) {
        if (left.size()>right.size()){
            right = lengthcheck(left,right);
        } else {left = lengthcheck(left,right);}
    }
    for (int i=left.size()-1;i>=0;i--) {
        sub = left[i] - right[i] + carry;
        if (sub < 0) {
            sub += 10;
            carry = -1;
            result.insert(result.begin(),sub);
        } else {
            carry = 0;
            result.insert(result.begin(),sub);
        }
    } 
    if (carry == -1) {
        result.at(0) = result.at(0)+carry;
    }
    return result;
}

/*
    According to Merriam-webster.com, Freebasing is "to prepare or use freebase cocaine"
    Used, here to pump up the vector to the correct base
*/
vector<int> freebasing(vector<int> a, int base) {
    for (int i=0;i<base;i++) {
        a.push_back(0);
    }
    return a; 
}

/*
    Simple resizer between two vectors, returning the smaller vector with
    enough 0's prepended to equal longer vectors length
*/
vector<int> lengthcheck(vector<int> first, vector<int> second) {
        int diff;
        if (first.size()>second.size()) {
            diff = first.size()-second.size();
            for (int i=0;i<diff;i++){
                second.insert(second.begin(),0);
            } 
            return second;
        } else {
            diff = second.size()-first.size();
            for (int i=0;i<diff;i++){
                first.insert(first.begin(),0);
            }
            return first;
        }
}
