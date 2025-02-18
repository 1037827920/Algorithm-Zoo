#include <iostream>
#include <list>
#include <unordered_map>

// LRU需要一个双向链表和一个哈希表来维护
// 哈希表来实现快速访问，而双向链表模拟一个键过期的操作
class LRUCache {
    struct CacheNode {
        int key;
        int value;
        CacheNode(int k, int v) : key(k), value(v) {}
    };

    size_t capacity; // 缓存容量
    std::list<CacheNode> cacheList;
    std::unordered_map<int, std::list<CacheNode>::iterator> keyMap; // 通过键映射到缓存节点的迭代器
public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (keyMap.find(key) == keyMap.end()) {
            return -1; // key不存在
        }

        // 将访问的节点移动到链表头部
        cacheList.splice(cacheList.begin(), cacheList, keyMap[key]);
        keyMap[key] = cacheList.begin(); // 更新哈希表指向
        return keyMap[key]->value;
    }

    void set(int key, int value) {
        // 如果要设置的键值已经存在
        if (keyMap.find(key) != keyMap.end()) {
            // 更新现有value
            keyMap[key]->value = value;
            // 更新过期时间
            cacheList.splice(cacheList.begin(), cacheList, keyMap[key]);
            keyMap[key] = cacheList.begin();
            return;
        }

        // 如果容量已满淘汰末尾元素
        if (cacheList.size() == capacity) {
            int delKey = cacheList.back().key;
            keyMap.erase(delKey);
            cacheList.pop_back();
        }

        // 插入新节点到list头部
        cacheList.emplace_front(key, value);
        keyMap[key] = cacheList.begin();
    }

    void printCache() {
        std::cout << "LRU Cache [ ";
        for (const auto& node : cacheList) {
            std::cout << "(" << node.key << ":" << node.value << ") ";
        }
        std::cout << "]\n";
    }
};

int main() {
    LRUCache cache(2);

    cache.set(1, 10);
    cache.set(2, 20);
    std::cout << cache.get(1) << std::endl;

    cache.set(3, 30);
    std::cout << cache.get(2) << std::endl;

    cache.set(1, 100);
    std::cout << cache.get(1) << std::endl;

    cache.printCache();

    return 0;
}