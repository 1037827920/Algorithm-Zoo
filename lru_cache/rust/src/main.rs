use std::{
    cell::RefCell,
    collections::HashMap,
    rc::{Rc, Weak},
};

struct CacheNode {
    /// 键
    key: i32,
    /// 值
    value: i32,
    /// 前一个节点，使用Weak，避免循环引用
    prev: Option<Weak<RefCell<CacheNode>>>,
    /// 后一个节点
    next: Option<Rc<RefCell<CacheNode>>>,
}

struct LRUCache {
    /// 容量
    capacity: usize,
    /// 哈希表，从键映射到节点
    map: HashMap<i32, Rc<RefCell<CacheNode>>>,
    /// 链表头节点
    head: Option<Rc<RefCell<CacheNode>>>,
    /// 链表尾节点
    tail: Option<Weak<RefCell<CacheNode>>>,
}

impl LRUCache {
    fn new(capacity: usize) -> LRUCache {
        LRUCache {
            capacity,
            map: HashMap::with_capacity(capacity),
            head: None,
            tail: None,
        }
    }

    /// 查询操作
    fn get(&mut self, key: i32) -> i32 {
        // 先检查键是否存在
        if !self.map.contains_key(&key) {
            return -1; // 不存在直接返回-1
        }

        // 已确认键存在，安全地获取节点
        let cache_node = self.map.get(&key).unwrap();
        let value = cache_node.borrow().value;

        // 更新LRU缓存状态，即将CacheNode移动到head
        let cache_node_cloned = Rc::clone(cache_node);
        self.remove_node(&cache_node_cloned);
        self.push_front(cache_node_cloned);

        // 返回value
        value
    }

    /// 插入/更新操作
    fn set(&mut self, key: i32, value: i32) {
        // 判断是否已经存在键，如果已经存在，需要更新值和链表
        if self.map.contains_key(&key) {
            let cache_node = self.map.get(&key).unwrap();
            let cache_node_cloned = Rc::clone(cache_node);
            cache_node_cloned.borrow_mut().value = value;
            self.remove_node(&cache_node_cloned);
            self.push_front(cache_node_cloned);
        } else {
            // 如果容量已满淘汰尾部节点
            if self.map.len() >= self.capacity {
                if let Some(tail_weak) = self.tail.take() {
                    if let Some(tail_rc) = tail_weak.upgrade() {
                        println!("容量已满，被移除的键是: {}", &tail_rc.borrow().key);
                        self.map.remove(&tail_rc.borrow().key);
                        self.remove_node(&tail_rc);
                    }
                }
            }

            // 创建新节点并插入
            let new_cache_node = Rc::new(RefCell::new(CacheNode {
                key,
                value,
                prev: None,
                next: None,
            }));
            self.push_front(Rc::clone(&new_cache_node));
            self.map.insert(key, new_cache_node);
        }
    }

    /// 将节点移动到链表头部
    fn push_front(&mut self, node: Rc<RefCell<CacheNode>>) {
        // 处理原来head节点的prev指针
        if let Some(head) = self.head.take() {
            let mut node_borrow = node.borrow_mut();
            head.borrow_mut().prev = Some(Rc::downgrade(&node));
            node_borrow.next = Some(head);
        } else {
            // 链表为空时更新尾指针
            self.tail = Some(Rc::downgrade(&node));
        }
        // 更新头指针
        self.head = Some(node);
    }

    /// 从链表中移除节点
    fn remove_node(&mut self, node: &Rc<RefCell<CacheNode>>) {
        let mut node_borrow = node.borrow_mut();
        // 处理prev节点
        if let Some(prev_weak) = node_borrow.prev.clone() {
            if let Some(prev_rc) = prev_weak.upgrade() {
                prev_rc.borrow_mut().next = node_borrow.next.clone();
            }
        }
        // 处理next节点
        if let Some(next_rc) = node_borrow.next.clone() {
            next_rc.borrow_mut().prev = node_borrow.prev.take();
        } else {
            // 被移除的节点是尾节点
            self.tail = node_borrow.prev.take();
        }
        // 如果被移除的是head
        if let Some(head) = &self.head {
            if Rc::ptr_eq(head, node) {
                self.head = node_borrow.next.take();
            }
        }
    }

    /// 打印LRU链表
    #[allow(dead_code)]
    fn print_list(&self) {
        let cache_node = self.head.clone().unwrap();
        println!("head: {}", cache_node.borrow().key);
        if let Some(cache_node) = self.tail.clone() {
            let cache_node = cache_node.upgrade().unwrap();
            println!("tail: {}", cache_node.borrow().key);
        }
    }
}

fn main() {
    let mut cache = LRUCache::new(2);
    cache.set(1, 1);
    cache.set(2, 2);
    assert_eq!(cache.get(1), 1);
    cache.set(3, 3);
    assert_eq!(cache.get(2), -1);
    assert_eq!(cache.get(3), 3);
    cache.set(1, 10);
    assert_eq!(cache.get(1), 10);
}
