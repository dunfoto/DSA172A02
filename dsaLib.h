/*
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : Library for Assignment 2 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */

#ifndef A02_DSALIB_H
#define A02_DSALIB_H

#include <string>
#include <math.h>
#include <vector>

using namespace std;

typedef enum {LH, EH, RH} _state;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
class List {
public:
    virtual void    clean() = 0;
    virtual void    clone(void*) = 0;
    virtual bool    isEmpty() = 0;
    virtual size_t  getSize() = 0;
    virtual T&      at(int i) = 0;
    virtual T&      operator[](int i) = 0;

    virtual bool    find(T& a, int& idx) = 0;
    virtual T*      find(T& a) = 0;
    virtual T*      find(T& a, std::function<bool (T&, T&)> eqCmp) = 0;
    virtual int     insert(int i, T& a) = 0;
    virtual int     insert(int i, T&& a) = 0;
    virtual int     remove(int i) = 0;
    virtual int     remove(T& a, std::function<bool (T&, T&)> eqCmp) = 0;

    virtual int     push_back(T& a) = 0;
    virtual int     push_back(T&& a) = 0;
    virtual int     insertHead(T& a) = 0;
    virtual int     insertHead(T&& a) = 0;
    virtual int     removeHead() = 0;
    virtual int     removeLast() = 0;

    virtual void    traverse(std::function<void (T&)> op) = 0;
    virtual void    traverse(std::function<void (T&, void*)> op, void* pParam) = 0;

    virtual void    reverse() = 0;
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;

    L1Item(T &a) : data(a), pNext(NULL) {}
    L1Item(T &a, void* next) : data(a), pNext(next) {}
    L1Item(T &&a) : data(std::move(a)), pNext(NULL) {}
    L1Item(T &&a, void* next) : data(std::move(a)), pNext(next) {}
};

template <class T>
class L1List : public List<T> {
    L1Item<T>   *_pHead;
    size_t      _size;
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List();

    void    clean();
    void    clone(void*);
    bool    isEmpty() { return _pHead == NULL; }
    size_t  getSize() { return _size; }

    T&      at(int i);
    T&      operator[](int i);

    bool    find(T& a, int& idx);
    T*      find(T& a);
    T*      find(T& a, std::function<bool (T&, T&)> eqCmp);//bool (*eqCmp)(T&, T&));
    int     insert(int i, T& a);
    int     insert(int i, T&& a);
    int     remove(int i);
    int     remove(T& a, std::function<bool (T&, T&)> eqCmp);

    int     push_back(T& a);
    int     push_back(T&& a);
    int     insertHead(T& a);
    int     insertHead(T&& a);
    int     removeHead();
    int     removeLast();

    void    reverse();

    void    traverse(std::function<void (T&)> op) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data);
            p = p->pNext;
        }
    }
    //void    traverse(void (*op)(T&, void*), void* pParam) {
    void    traverse(std::function<void (T&, void*)> op, void* pParam) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data, pParam);
            p = p->pNext;
        }
    }
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(a);
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(a);
    }

    _size++;
    return 0;
}

template <class T>
int L1List<T>::push_back(T &&a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(std::move(a));
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(std::move(a));
    }

    _size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
    L1Item<T>   *p = new L1Item<T>(a);
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

template <class T>
int L1List<T>::insertHead(T&& a) {
    L1Item<T>   *p = new L1Item<T>(std::move(a));
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
    if(_pHead) {
        L1Item<T>* p = _pHead;
        _pHead = p->pNext;
        delete p;
        _size--;
        return 0;
    }
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
    if(_pHead) {
        if(_pHead->pNext) {
            L1Item<T>* prev = _pHead;
            L1Item<T>* pcur = prev->pNext;
            while(pcur->pNext) {
                prev = pcur;
                pcur = pcur->pNext;
            }
            delete pcur;
            prev->pNext = NULL;
        }
        else {
            delete _pHead;
            _pHead = NULL;
        }
        _size--;
        return 0;
    }
    return -1;
}

/************************************************************************
 * This section is for AVL tree
 ************************************************************************/
template <class T>
struct AVLNode {
    T           _data;
    AVLNode<T>   *_pLeft, *_pRight;
    _state state;
#ifdef AVL_USE_HEIGHT
    int         _height;
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _height(1), state(EH) {}
#else
    int         _bFactor;
    AVLNode(T &a) : _data(a), _pLeft(NULL), _pRight(NULL), _bFactor(0), state(EH) {}
#endif
};

template <class T>
class AVLTree {
    AVLNode<T> *_pRoot;
public:
    AVLTree() : _pRoot(NULL) {}
    ~AVLTree() { destroy(_pRoot); }

    bool find(T& key, T* &ret) { return find(_pRoot, key, ret); }
    bool insert(T& key) { return insert(_pRoot, key); }
    bool remove(T& key) { return remove(_pRoot, key); }
    void traverseNLR(void (*op)(T&)) { traverseNLR(_pRoot, op); }
    void traverseLNR(void (*op)(T&)) { traverseLNR(_pRoot, op); }
    void traverseLRN(void (*op)(T&)) { traverseLRN(_pRoot, op); }

protected:
    void destroy(AVLNode<T>* &pR); //done
    bool find(AVLNode<T> *pR, T& key, T* &ret); //done
    bool insert(AVLNode<T>* &pR, T& a); //done
    void _insert(AVLNode<T>* &pR,T& a,bool &isTaller,bool IsLeft); //done
    bool remove(AVLNode<T>* &pR, T& a); //done
    void _remove(AVLNode<T>* &pR, T& a, bool *shorter, bool *success); //done
    void traverseNLR(AVLNode<T> *pR, void (*op)(T&)); //done
    void traverseLNR(AVLNode<T> *pR, void (*op)(T&)); //done
    void traverseLRN(AVLNode<T> *pR, void (*op)(T&)); //done

    void rotLeft(AVLNode<T>* &pR); //done
    void rotRight(AVLNode<T>* &pR); //done
    void rotLR(AVLNode<T>* &pR); //?
    void rotRL(AVLNode<T>* &pR); //?

    bool balanceLeft(AVLNode<T>* &pR); //done
    bool balanceRight(AVLNode<T>* &pR); //done
    void dltRightbal(AVLNode<T>* &pR); //done
    void dltLeftBal(AVLNode<T>* &pR);//done
};

/*definition for functions of AVL Tree */
//1. detroy an AVL tree
template <class T>
void AVLTree<T>::destroy(AVLNode<T>* &pR){
    if (pR->_pLeft != NULL){
        destroy(pR->_pLeft);
    }
    if (pR->_pRight != NULL){
        destroy(pR->_pRight);
    }
    delete pR;
    pR = NULL;
}
//2. find a node containing value [key] and assign the node the pointer [ret]
template <class T>
bool find(AVLNode<T> *pR, T& key, T* &ret){
    if (pR == NULL){ //[key] does not exist! return false and set pointer to NULl
        ret = NULL;
        return false;
    }else{
        if (pR->_data == key){ //return the value
            ret = pR;
            return true;
        }
        else if (pR->_data < key){ //search the [key] in the right side of the tree
            return find(pR->_pRight,key,ret);
        }
        else{
            return find(pR->_pLeft,key,ret);
        }
    }
}
//3. insert an AVL Node
template<class T>
bool insert(AVLNode<T>* &pR, T& a){
    bool isTaller = false;
    bool IsLeft = false;
    int level = 0;
    return _insert(pR,a,isTaller, IsLeft, level);
}
template<class T>
void _insert(AVLNode<T>* &pR,T& a,bool &isTaller,bool IsLeft){
    //pR == NULL -> insert
    if (pR == NULL){
        isTaller = true;
        pR->_data = a;
    }
    else{ //root != NULL
        if(a < pR->_data){
            _insert(pR->_pLeft,a,isTaller,true);
            if (isTaller){
                if (pR->state ==RH){
                    pR->state = EH;
                    isTaller = false;
                }
                else if (pR->state == LH){
                    balanceLeft(pR);
                    isTaller = false;
                }
                else{
                    pR->state = LH;
                }
            }
        }
        else if (a > pR->_data){
            _insert(pR->_pRight,a,isTaller,true);
            if (isTaller) {
                if (pR->state == LH) {
                    pR->state = EH;
                    isTaller = false;
                }
                else if (pR->state == RH){
                    balanceRight(pR);
                    isTaller - false;
                }
                else {
                    pR->state = RH;
                }
            }
        }
        else{
            isTaller = false;
        }
    }
}
template<class T>
void rotLeft(AVLNode<T>* &pR){
    AVLNode<T>* tmp = pR;
	pR = tmp->_pRight;
	tmp->_pRight = pR->_pLeft;
	pR->_pLeft = tmp;
}
template<class T>
void rotRight(AVLNode<T>* &pR){
    AVLNode<T> *tmp = pR;
    pR = tmp->_pLeft;
    tmp->_pLeft = pR->_pRight;
    pR->_pRight = tmp;
}
template<class T>
bool balanceLeft(AVLNode<T>* &pR){
    if (pR->_pLeft->state == LH){
        pR->_pLeft->state = EH;
        pR->state = EH;
        rotRight(pR);
    }
    else{
        if (pR->_pLeft->_pRight->state == LH){
            pR->state = RH;
            pR->_pLeft->state = EH;
        }
        else if (pR->_pLeft->_pRight->state == EH){
            pR->state = EH;
            pR->_pLeft->state = EH;
        }
        else{
            pR->state = EH;
            pR->_pLeft->state = LH;
        }
        pR->_pLeft->_pRight->state = EH;
        rotLeft(pR->_pLeft);
        rotRight(pR);
    }
}
template<class T>
bool balanceRight(AVLNode<T>* &pR){
    if (pR->_pRight->state == RH){
        pR->_pRight->state = EH;
        pR->state = EH;
        rotLeft(pR);
    }
    else {
        if (pR->_pRight->_pLeft->state == RH) {
            pR->state = LH;
            pR->_pRight->state = EH;
        }
        else if (pR->_pRight->_pLeft->state == EH){
            pR->state = EH;
            pR->_pRight->state = EH;
        }
        else {
            pR->state = EH;
            pR->_pRight->state = RH;
        }
        pR->_pRight->_pLeft->state = EH;
        rotRight(pR->_pRight);
        rotLeft(pR);
    }
}

template<class T>
bool remove(AVLNode<T>* &pR, T& a){
    bool shorter;
    bool success;
    _remove(pR,a,shorter,success);
    return success;
}
template<class T>
void _remove(AVLNode<T>* &pR, T& a, bool *shorter, bool *success){
    AVLNode<T>* dltPtr;
    AVLNode<T>* exchPtr;
    AVLNode<T>* newRoot;
    if(!pR){
        *shorter = false;
        *success = false;
        return;
    }
    if (a < pR->_data){
        _remove(pR->_pLeft,a,shorter,success);
        if (*shorter)
            dltRightBal(pR, shorter);
    }
    else if (a > pR->_data){
        _remove(pR->_pRight,a,shorter,success);
        if (*shorter)
            dltLeftbal(pR,shorter);
    }
    else{
        dltPtr = pR;
        if (!pR->_pRight){
            pR = pR->_pLeft;
            delete dltPtr;
            *success = true;
            *shorter = true;
        }
        else if (!pR->_pLeft){
            pR = pR->_pLeft;
            delete dltPtr;
            *success = true;
            *shorter = true;
        }
        else{
            exchPtr = pR->_pLeft;
            while (exchPtr->_pRight)
                exchPtr = exchPtr->_pRight;
            pR->_data = exchPtr->_data;
            _remove(pR->left,exchPtr->_data,shorter,success);
            if (*shorter)
                dltRightBal(pR,shorter);
        }
    }
}

template<class T>
void dltRightBal(AVLNode<T>* &pR, bool *shorter){
    switch (pR->state) {
        case LH:
            pR->state = EH;
            break;
        case EH:
            pR->state = RH;
            *shorter = false;
            break;
        case RH:
            if (pR->_pRight->state == LH){
                switch (pR->_pRight->_pLeft->state){
                    case LH:
                        pR->_pRight->state = RH;
                        pR->state = EH;
                        break;
                    case EH:
                        pR->_pRight->state = EH;
                        pR->state = EH;
                        break;
                    case RH:
                        pR->_pRight->state = EH;
                        pR->state = LH;
                        break;
                }
                pR->_pRight->_pLeft->state = EH;
                rotRight(pR->_pRight);
                rotLeft(pR);
            }
            else{
                switch (pR->_pRight->state){
                    case LH:
                    case RH:
                        pR->_pRight->state = EH;
                        pR->state = EH;
                        break;
                    case EH:
                        pR->_pRight->state = LH;
                        pR->state = RH;
                        break;
                }
                rotLeft(pR);
            }
    }
}

template<class T>
void dltLeftBal(AVLNode<T>* &pR, bool *shorter){
    switch (pR->state){
        case RH:
            pR->state = EH;
            break;
        case EH:
            pR->state = LH;
            *shorter = false;
            break;
        case LH:
            if (pR->_pLeft->state == RH){
                switch (pR->_pLeft->_pRight->state){
                    case RH:
                        pR->_pLeft->state = LH;
                        pR->state = EH;
                        break;
                    case EH:
                        pR->_pLeft->state = EH;
                        pR->state = EH;
                        break;
                    case LH:
                        pR->_pLeft->state = EH;
                        pR->state = RH;
                        break;
                }
                pR->_pLeft->_pRight->state = EH;
                rotLeft(pR->_pLeft);
                rotRight(pR);
            }
            else{
                switch (pR->_pLeft->state){
                    case EH:
                    case LH:
                        pR->_pLeft->state = EH;
                        pR->state = EH;
                        break;
                    case EH:
                        pR->_pLeft->state = RH;
                        pR->state = LH;
                        break;
                }
                rotRight(pR);
            }
    }
}

template<class T>
void traverseNLR(AVLNode<T> *pR, void (*op)(T&)){
    if (pR){
        //print data node hiện tại
        traverseNLR(pR->_pLeft, op());
        traverseNLR(pR->_pRight, op());
    }
}
template<class T>
void traverseLNR(AVLNode<T> *pR, void (*op)(T&)){
    if (pR){
        traverseLNR(pR->_pLeft, op());
        //print data node hiện tại
        traverseLNR(pR->_pRight, op());
    }
}
template<class T>
void traverseLRN(AVLNode<T> *pR, void (*op)(T&)){
    if (pR){
        traverseLRN(pR->_pLeft, op());
        traverseLRN(pR->_pRight, op());
        //print data node hiện tại
    }
}
#endif //A02_DSALIB_H
