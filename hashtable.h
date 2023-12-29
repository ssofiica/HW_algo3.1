#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

static constexpr int HASH_TABLE_DEFAULT_SIZE = 8;
static constexpr float HASH_TABLE_MAX_KEYS_FILL = 0.75;
static constexpr float HASH_TABLE_MAX_DELETE_FILL = 0.25;

enum TypeOfNode {
    d, // deleted
    k, // key
    e, // empty/nil
};

template<typename T>
struct HashTableNode {
public:
    HashTableNode() : key(), nodeType(TypeOfNode::e) {}
    TypeOfNode nodeType;
    T key;
};


template<typename T, typename Hasher = std::hash<T>>
class HashTable {
public:
    explicit HashTable(size_t default_size = HASH_TABLE_DEFAULT_SIZE) : table(default_size), size(0), delete_nodes(0) {}

    ~HashTable() = default;

    bool Add(const T& key) {

        if (size >= HASH_TABLE_MAX_KEYS_FILL * table.size()) {
            grow();
        }

        unsigned int hash = hasher(key) % table.size();
        bool firstDeletedNode = true;
        unsigned int firstDeletedNodeIndex = 0;
        for (size_t i = 0; i < table.size(); ++i) {
            hash = (hash + i) % table.size();
            switch (table[hash].nodeType) {
            case TypeOfNode::e:
                if (!firstDeletedNode) {
                    table[firstDeletedNodeIndex].key = key;
                    table[firstDeletedNodeIndex].nodeType = TypeOfNode::k;
                    --delete_nodes;
                    ++size;
                    return true;
                }
                table[hash].key = key;
                table[hash].nodeType = TypeOfNode::k;
                ++size;
                return true;
            case TypeOfNode::d:
                if (firstDeletedNode) {
                    firstDeletedNodeIndex = hash;
                    firstDeletedNode = false;
                }
                break;
            case TypeOfNode::k:
                if (table[hash].key == key) return false;
                else break;
            }
        }
        return true;
    }

    bool Has(const T& key) {
        unsigned int hash = hasher(key) % table.size();
        for (int i = 0; i < table.size(); ++i) {
            hash = (hash + i) % table.size();
            switch (table[hash].nodeType) {
            case TypeOfNode::e:
                return false;
            case TypeOfNode::d:
                break;
            case TypeOfNode::k:
                if (table[hash].key == key) return true;
                else break;
            }
        }
        return false;
    }

    bool Delete(const T& key) {
        if (delete_nodes >= HASH_TABLE_MAX_DELETE_FILL * table.size()) {
            DDNodes();
        }
        unsigned int hash = hasher(key) % table.size();
        for (size_t i = 0; i < table.size(); ++i) {
            hash = (hash + i) % table.size();
            switch (table[hash].nodeType) {
            case TypeOfNode::e:
                return false;
            case TypeOfNode::d:
                break;
            case TypeOfNode::k:
                if (table[hash].key == key) {
                    table[hash].nodeType = TypeOfNode::d;
                    --size;
                    ++delete_nodes;
                    return true;
                }
                else break;
            }
        }
        return false;
    }

    std::vector<T> Data() const {
        std::vector<T> result;
        for (const auto& node : table) {
            if (node.nodeType == TypeOfNode::k) {
                result.push_back(node.key);
            }
        }
        return result;
    }

private:
    void grow() {
        std::vector<HashTableNode<T>> old_table(std::move(table));

        table.clear();
        table.resize(old_table.size() * 2);

        for (size_t i = 0; i < old_table.size(); ++i) {
            switch (old_table[i].nodeType) {
            case TypeOfNode::k:
                Add(old_table[i].key);
                break;
            default:
                break;
            }
        }
        delete_nodes = 0;
    }

    void DDNodes() {
        std::vector<HashTableNode<T>> old_table(table);

        std::fill(table.begin(), table.end(), HashTableNode<T>());

        for (size_t i = 0; i < old_table.size(); ++i) {
            switch (old_table[i].nodeType) {
            case TypeOfNode::k:
                Add(old_table[i].key);
                break;
            default:
                break;
            }
        }
        delete_nodes = 0;
    }

    std::vector<HashTableNode<T>> table;
    unsigned int size;
    unsigned int delete_nodes;
    Hasher hasher;
};


