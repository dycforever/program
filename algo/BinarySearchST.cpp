#include <common.h>
#include <rawlog.h>
#include <stack>
//#include <BinarySearchST.h>
using namespace std;
using namespace dyc;

template<typename K, typename V>
class BinarySearchST{
public:
    class Node{
        public:
        K m_key;
        V m_value;
        size_t m_size;
        Node* left;
        Node* right;
        Node* pre;
        Node* suc;
        Node(){}
        Node(K key, V value){
            m_key = key;
            m_value = value;
            m_size = 1;
            pre = suc = NULL;
        }
    };

private:
    Node* m_root;

    size_t rank(Node*, K);
    K select(Node*, size_t);
    size_t size(Node*);
    Node* delete_max(Node*);
    Node* delete_key(Node*, K);
    Node* get(Node*, K);
    Node* delete_min(Node*);
    Node* put(Node*, K, V);
    int get_height(Node*,int,int);

    Node* min(Node*);
    Node* max(Node*);

    int check_binary();
    int check_order_and_equal();
    int check_order_and_equal(Node*);
    int check_rank();

public:
    BinarySearchST();
    ~BinarySearchST();
    size_t size();
    size_t rank(K);
    K select(size_t);
    int get(K, V&);
    int delete_min();
    int delete_max();
    int delete_key(K);
    int put(K, V);
    int get_height();

    Node* min();
    Node* max();

    int check();
    int in_order_travel();
    int pre_order_travel();

    int threadlize();
};

template<typename K, typename V>
BinarySearchST<K,V>::~BinarySearchST(){
}

template<typename K, typename V>
BinarySearchST<K,V>::BinarySearchST(){
    m_root = NULL;
}

template<typename K, typename V>
int BinarySearchST<K, V>::put(K key, V value){
    m_root = put(m_root, key, value);
    if(NULL != m_root){
//        DEBUG("insert success");
        return 0;
    }
    WARN_LOG("insert failed");
    return -1;
}

template<typename K, typename V>
typename BinarySearchST<K,V>::Node* BinarySearchST<K, V>::put(Node* node, K key, V value){
    if(NULL == node){
        return NEW Node(key, value);
    }
    if(node->m_key == key){
        node->m_value = value;
    }else if(node->m_key < key){
        Node* tmp = put(node->right, key, value);
        if(NULL == tmp)
            return NULL;
        node->right = tmp;
    }else{
        Node* tmp = put(node->left, key, value);
        if(NULL == tmp)
            return NULL;
        node->left = tmp;
    }
    node->m_size = size(node->left) + size(node->right) + 1;
    return node;
}

template<typename K, typename V>
int BinarySearchST<K,V>::get(K key, V& value){
    Node* node = get(m_root, key); 
    if(NULL != node){
        value = node->m_value;
        return 0;
    }else{
        WARN_LOG("not found");
        return -1;
    }
}

template<typename K, typename V>
typename BinarySearchST<K,V>::Node* BinarySearchST<K,V>::get(Node* node, K key){
    if(NULL == node)
        return NULL;
    if(node->m_key < key){
        return get(node->right, key);
    }else if(node->m_key > key){
        return get(node->left, key);
    }else{
        return node;
    }
}

template<typename K, typename V>
size_t BinarySearchST<K,V>::size(){
    return size(m_root); 
}

template<typename K, typename V>
size_t BinarySearchST<K,V>::size(Node* node){
    if(NULL == node){
        return 0;
    }
    return node->m_size;
}

template<typename K, typename V>
size_t BinarySearchST<K,V>::rank(K key){
    int i = rank(m_root, key);
    return i;
}

template<typename K, typename V>
size_t BinarySearchST<K,V>::rank(Node* node, K key){
    if(NULL == node) return 0;
    if(key == node->m_key)
        return size(node->left);
    if(key <= node->m_key)
        return rank(node->left, key);
    if(key >= node->m_key)
        return size(node->left) +1 + rank(node->right, key); 
}

template<typename K, typename V>
K BinarySearchST<K,V>::select(size_t rank){
    return select(m_root, rank); 
}

template<typename K, typename V>
K BinarySearchST<K,V>::select(Node* node, size_t rank){
    if(rank > size(node->left)){
        return select(node->right, rank - size(node->left)-1);
    }else if(rank < size(node->left)){
        return select(node->left, rank);
    }else{
        return node->m_key;
    }
}

template<typename K, typename V>
int BinarySearchST<K,V>::delete_min(){
    m_root = delete_min(m_root);
    return 0;
}

template<typename K, typename V>
typename BinarySearchST<K,V>::Node* BinarySearchST<K,V>::delete_min(Node* node){
    if(NULL == node){
        return NULL;
    }
    Node* sub_root = NULL;
    if(node->left != NULL){
        node->left = delete_min(node->left);
        sub_root = node;
    }else{
        sub_root = node->right;
        DELETE(node);
    }
    if( NULL != sub_root)
        sub_root->m_size = size(sub_root->m_left)+1+size(sub_root->m_right);
    return sub_root;
}

template<typename K, typename V>
int BinarySearchST<K,V>::delete_max(){
    m_root = delete_max(m_root);
    return 0;
}

template<typename K, typename V>
typename BinarySearchST<K,V>::Node* BinarySearchST<K,V>::delete_max(Node* node){
    if(NULL == node){
        return NULL;
    }
    Node* sub_root = NULL;
    if(node->right!= NULL){
        node->right = delete_max(node->right);
        sub_root = node;
    }else{
        sub_root = node->left;
        DELETE(node);
    }
    sub_root->m_size = size(sub_root->m_left)+1+size(sub_root->m_right);
    return sub_root;
}

template<typename K, typename V>
typename BinarySearchST<K,V>::Node* BinarySearchST<K,V>::min(){
    return min(m_root);
}

template<typename K, typename V>
typename BinarySearchST<K,V>::Node* BinarySearchST<K,V>::min(Node* node){
    if(NULL == node){
        return NULL;
    }
    if(NULL != node->left)
        return min(node->left);
    return node;
}

template<typename K, typename V>
typename BinarySearchST<K,V>::Node* BinarySearchST<K,V>::max(){
    return max(m_root);
}

template<typename K, typename V>
typename BinarySearchST<K,V>::Node* BinarySearchST<K,V>::max(Node* node){
    if(NULL == node){
        return NULL;
    }
    if(node->right != NULL){
        return max(node->right);
    }else{
        return node;
    }
}

template<typename K, typename V>
int BinarySearchST<K,V>::delete_key(K key){
    m_root = delete_key(m_root, key);
    return 0;
}

template<typename K, typename V>
typename BinarySearchST<K,V>::Node* BinarySearchST<K,V>::delete_key(Node* node,K key){
    if(NULL == node){
        return NULL;
    }
    if(key < node->m_key) return delete_key(node->left, key);
    if(key > node->m_key) return delete_key(node->right, key);
    Node* successor = min(node->right);
    if(successor != NULL){
        successor->right = delete_min(node->right);
        successor->left = node->left;
        return successor;
    }
    Node* tmp = node->left;
    DELETE(node);
    return tmp;
}

template<typename K, typename V>
int BinarySearchST<K,V>::check_binary(){
    int max_height = m_root->m_size; 
    int ret = get_height(m_root, 1, max_height);
    if(ret == -1)
        return -1;
    if( size(m_root) != m_root->m_size){
        FATAL_LOG("inconsistent node size ");
        return -1;
    }
    return 0;
}

template<typename K, typename V>
int BinarySearchST<K,V>::get_height(Node* node, int now_layer, int max){
    if(NULL == node)
        return 0;
    if(now_layer > max){
        FATAL_LOG("too many layer:%d  max:%d", now_layer, max);
        return -1;
    }
    int left_h = get_height(node->left, now_layer+1, max);
    int right_h = get_height(node->right, now_layer+1, max);
    if(left_h == -1 || right_h == -1)
        return -1;
    int height = left_h > right_h ? left_h:right_h;
    return 1+height;
}

template<typename K, typename V>
int BinarySearchST<K,V>::check_rank(){
    if(m_root == NULL)
        return 0;
    for(int i=0;i<m_root->m_size;++i){
        if( rank(select(i)) != i){
            FATAL_LOG("check rank failed i:%d",i);
            return -1;
        }
//        DEBUG("check rank select success");
    }
    return 0;
}

template<typename K, typename V>
int BinarySearchST<K,V>::check_order_and_equal(){
    return check_order_and_equal(m_root);
}

template<typename K, typename V>
int BinarySearchST<K,V>::check_order_and_equal(typename BinarySearchST<K,V>::Node* node){
    if(node == NULL)
        return 0;
    if( node->left && node->left->m_key >= node->m_key ){
        FATAL_LOG("invalid order at left");
        cout << "left child:" << node->left->m_key <<"  self:" << node->m_key << endl;
        return -1;
    }

    if( node->right && node->right->m_key <= node->m_key){
        FATAL_LOG("invalid order at right");
        cout << "right child:" << node->right->m_key <<"  self:" << node->m_key << endl;
        return -1;
    }
    int ret;
    ret = check_order_and_equal(node->left);
    if( 0 != ret){
        FATAL_LOG("invalid order in left subtree");
        return -1;
    }
    ret = check_order_and_equal(node->right);
    if( 0 != ret){
        FATAL_LOG("invalid order in right subtree");
        return -1;
    }
    return 0;
}

template<typename K, typename V>
int BinarySearchST<K,V>::get_height(){
    return get_height(m_root, 1, m_root->m_size);
}

template<typename K, typename V>
int BinarySearchST<K,V>::check(){
    int ret;
    ret = check_binary();
    if(0 != ret){
        FATAL_LOG("check binary failed");
        return -1;
    }

    ret = check_order_and_equal();
    if(0 != ret){
        FATAL_LOG("check order failed");
        return -1;
    }

    ret = check_rank();
    if(0 != ret){
        FATAL_LOG("check rank failed");
        return -1;
    }
    return 0;
}

template<typename K, typename V>
int BinarySearchST<K,V>::in_order_travel(){
    stack<Node*> stack;
    stack.push(m_root);
    while(!stack.empty()){
        Node* node = stack.top();
        while(node != NULL){
            stack.push(node->left);
            node = node->left;
        }
        stack.pop();
        if(!stack.empty()){
            node = stack.top();
            stack.pop();
            cout << node->m_key << " ";
        }
        if(node != NULL)
            stack.push(node->right);
    }
    cout << endl;
    return 0;
}

template<typename K, typename V>
int BinarySearchST<K,V>::pre_order_travel(){
    stack<Node*> stack;
    stack.push(m_root);
    while(!stack.empty()){
        Node* node = stack.top();
        while(node != NULL){
            cout << node->m_key << " ";
            stack.push(node->left);
            node = node->left;
        }
        stack.pop();
        if(!stack.empty()){
            node = stack.top();
            stack.pop();
        }
        if(node != NULL)
            stack.push(node->right);
    }
    cout << endl;
    return 0;
}

template<typename K, typename V>
int BinarySearchST<K,V>::threadlize(){
    Node* pre = NULL;
    Node* cur = NULL;
    stack<Node*> stack;
    stack.push(m_root);
    while(!stack.empty()){
        Node* node = stack.top();
        while(node != NULL){
            stack.push(node->left);
            node = node->left;
        }
        stack.pop();
        if(!stack.empty()){
            node = stack.top();
            stack.pop();
            node->pre = pre;
            if(pre != NULL){
                pre->suc = node;
            }
            pre = node;
        }
        if(node != NULL)
            stack.push(node->right);
    }
    return 0;
}

int main() {
    BinarySearchST<string,int> st;
    char* buffer = NEW char[1024];
    st.put("E",1);
    st.put("D",1);
    st.put("Q",1);
    st.put("A",1);
    st.put("J",1);
    st.put("T",1);
    st.put("M",1);
    st.put("S",1);
    cout <<"height: " <<  st.get_height() << endl;

    st.check();
    cout << "pre order travel:" << endl;
    st.pre_order_travel();
    cout << "in order travel:" << endl;
    st.in_order_travel();
    st.threadlize();
    cout << "after threadlize:" << endl;
    for(BinarySearchST<string, int>::Node* n=st.min(); n != NULL; n = n->suc)
        cout << n->m_key << " ";
    cout << endl;
}

