/*
 * abb.cpp
 *
 *  Created on: Sep 2, 2022
 *      Author: jsaavedr
 */

#include "trees/rb.hpp"
#include <iostream>
#include <chrono>

namespace trees {

RB::RB():root(nullptr) {
	// TODO Auto-generated constructor stub
}

void RB::balance(RBNode* node){
    RotationType rType = getRotationType(node);
    switch (rType) {
        case RotationType::case_1:
            // Implementa lógica para el caso 1
            break;
        case RotationType::case_2:
            // Implementa lógica para el caso 2
            break;
        case RotationType::case_3:
            // Implementa lógica para el caso 3
            break;
        // Agrega más casos según sea necesario
    }
}

RotationType RB::getRotationType(RBNode* node){
	/*this will run if node is unbalanced*/
	RotationType rType = RotationType::case_1;
	//TODO
	return rType;
}

void RB::do_case_1(RBNode* node){
	RBNode* parent = node->getParent();
    RBNode* grandparent = parent ? parent->getParent() : nullptr;
    RBNode* uncle = grandparent ? (grandparent->getLeft() == parent ? grandparent->getRight() : grandparent->getLeft()) : nullptr;
    if (uncle && uncle->getColor() == NodeColor::RED) {
        parent->setColor(NodeColor::BLACK);
        uncle->setColor(NodeColor::BLACK);
        grandparent->setColor(NodeColor::RED);
        balance(grandparent);
    } else if (!parent->getParent()) {
        parent->setColor(NodeColor::BLACK);
    }
}

void RB::do_case_2(RBNode* node){
	RBNode* parent = node->getParent();
    RBNode* grandparent = parent->getParent();
    if (parent == grandparent->getLeft()) {
        rotateRight(grandparent);
    } else {
        rotateLeft(grandparent);
    }
    parent->setColor(NodeColor::BLACK);
    grandparent->setColor(NodeColor::RED);
}

void RB::do_case_3(RBNode* node){
	RBNode* parent = node->getParent();
    RBNode* grandparent = parent->getParent();
    if (node == parent->getRight() && parent == grandparent->getLeft()) {
        rotateLeft(parent);
        node = node->getLeft();
    } else if (node == parent->getLeft() && parent == grandparent->getRight()) {
        rotateRight(parent);
        node = node->getRight();
    }
    do_case_2(node);
}

void RB::rotateLeft(RBNode* node) {
    RBNode* rightChild = node->getRight();
    node->setRight(rightChild->getLeft());

    if (rightChild->getLeft() != nullptr) {
        rightChild->getLeft()->setParent(node);
    }

    rightChild->setParent(node->getParent());
    if (node->getParent() == nullptr) {
        root = rightChild;
    } else if (node == node->getParent()->getLeft()) {
        node->getParent()->setLeft(rightChild);
    } else {
        node->getParent()->setRight(rightChild);
    }

    rightChild->setLeft(node);
    node->setParent(rightChild);
}

void RB::rotateRight(RBNode* node) {
    RBNode* leftChild = node->getLeft();
    node->setLeft(leftChild->getRight());

    if (leftChild->getRight() != nullptr) {
        leftChild->getRight()->setParent(node);
    }

    leftChild->setParent(node->getParent());
    if (node->getParent() == nullptr) {
        root = leftChild;
    } else if (node == node->getParent()->getRight()) {
        node->getParent()->setRight(leftChild);
    } else {
        node->getParent()->setLeft(leftChild);
    }

    leftChild->setRight(node);
    node->setParent(leftChild);
}

void RB::insert(int val, RBNode* node){

	if (val < node->getData()){
		if (node->getLeft() == nullptr){
			node->setLeft(new RBNode(val, node));
			balance(node->getLeft());
		}
		else{
			insert(val, node->getLeft());
		}
	}
	else{
		if (node->getRight() == nullptr){
			node->setRight(new RBNode(val, node));
			balance(node->getRight());
		}
		else{
			insert(val, node->getRight());
		}
	}
}

void RB::insert(int val){
	if (root == nullptr){
		root = new RBNode(val);
		root->setColor(NodeColor::BLACK);
    }
	else{
		insert(val, root);
	}
}

RBNode* RB::find(int val, RBNode* node){
	RBNode* ans = nullptr;
	if (node->getData() == val){
		ans = node;
	}
	else{
		if (val < node->getData()){
			ans = find(val, node->getLeft());
		}
		else{
			ans = find(val, node->getRight());
		}
	}
	return ans;
}

RBNode* RB::find(int val){
	RBNode* ans = nullptr;
	ans = find(val, root);
	return ans;
}

void RB::traverse(RBNode* node, int label){
	if (node != nullptr){
		for (int i = 0; i < label; i++){
			std::cout << "*" << std::flush;
		}
		char T = node->isLeft()?'L':'R';
		std::cout << node->getData() << "  " << T <<std::endl;
		traverse(node->getLeft(), label + 1);
		traverse(node->getRight(), label + 1);
	}
}

void RB::traverse(){
	traverse(root, 1);
}


RB::~RB() {
	delete root;
}

} /* namespace trees */
