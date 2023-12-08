#include <iostream>
#include <string>

// 怪物节点定义
struct MonsterNode {
	std::string name;
	int health;
	int damage;
	MonsterNode* left;
	MonsterNode* right;

	MonsterNode(const std::string& monsterName, int monsterHealth, int monsterDamage)
		: name(monsterName), health(monsterHealth), damage(monsterDamage), left(nullptr), right(nullptr) {}
};

// 先序遍历怪物二叉树
void preorderTraversal(MonsterNode* root) {
	if (root) {
		std::cout << "Monster: " << root->name << " (Health: " << root->health << ", Damage: " << root->damage << ")" << std::endl;
		preorderTraversal(root->left);
		preorderTraversal(root->right);
	}
}

// 释放怪物二叉树的内存
void deleteMemory(MonsterNode* root) {
	if (root){
		deleteMemory(root->left);
		deleteMemory(root->right);
		delete root;
	}

}


int main() {
	// 创建一个怪物二叉树
	MonsterNode* root = new MonsterNode("Dragon", 1000, 50);
	root->left = new MonsterNode("Orc", 500, 30);
	root->right = new MonsterNode("Goblin", 200, 10);
	root->left->left = new MonsterNode("Troll", 800, 40);
	root->left->right = new MonsterNode("Minotaur", 1200, 60);
	root->right->left = new MonsterNode("Skeleton", 150, 5);

	// 执行先序遍历并输出怪物信息
	std::cout << "怪物二叉树:" << std::endl;
	preorderTraversal(root);

	system("pause");

	// 释放怪物二叉树的内存
	deleteMemory(root);
	
	// 在实际应用中需要注意内存管理

	return 0;
}
