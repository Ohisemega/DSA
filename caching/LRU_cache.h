#include <list>
#include <unordered_map>
#include <cstdint>
#include <optional>

template <typename V>
class LRUCache {
    using node_t = std::pair<int, V>;
    public:
        LRUCache(uint64_t max_size) : size_{0}, max_size_{max_size} {
            mmap_.reserve(max_size);
        }

        void put(node_t&& node){
            if(mmap_.count(node.first)){
                qu_.erase(mmap_[node.first]);
                mmap_.erase(node.first);
                qu_.push_front(node);
                mmap_[node.second] = qu_.begin();
            }else {
                if(size_ == max_size_) {
                    mmap_.erase(node.first);
                    qu_.pop_back();
                } else {
                    ++size_;
                }
                qu_.push_front(node);
                mmap_[node.first] = qu_.begin();
            }
        }

        std::optional<V> get(const uint64_t key) const {
            if(mmap_.count(key)) {
                V val = (*mmap_[key]).second;
                qu_.erase(mmap_[key]);
                mmap_.erase(key);
                qu_.push_front({key, val});
                mmap_[key] = qu_.begin();
                return val;
            }
            return {};
        }
        
        uint64_t size() const {
            return size_;
        }

    private:
        typedef uint64_t ptr_t;
        std::unordered_map<uint64_t, typename std::list<node_t>::iterator> mmap_;
        std::list<std::pair<int, V>> qu_;
        const uint64_t max_size_;
        uint64_t size_;
};
