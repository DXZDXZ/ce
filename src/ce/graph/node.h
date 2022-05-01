#include <set>
#include <limits>
#include <string>

#include "ce/graph/basic_types.h"

namespace ce
{
class NodeArg{

};

class Node{
public:
    ~Node() = default;
    NodeIndex Index() const noexcept{ return index_; }
    
    /**
     * @brief 边节点，表示当前节点输入或者输出边另一端的端节点
     * Node内部类：class ce::Node::EdgeEnd
     */
    class EdgeEnd{
    public:
        // C++ 小课堂
        // noexcept 修饰的函数不会在执行过程中抛出异常，如果发生异常，编译器会调用std::terminate()函数中断程序执行
        // 优点：
        // 缺点：
        EdgeEnd(const Node& node, int src_index, int dst_index) noexcept;
        explicit EdgeEnd(const Node& node) noexcept;

        const Node& GetNode() const noexcept{
            return *node_;
        }

        int GetSrcIndex() const{
            return src_index_;
        }

        int GetDstIndex() const{
            return dst_index_;
        }

    private:
        Node* node_;
        const int src_index_;
        const int dst_index_;
    };

    /**
     * @brief 定义EdgeEnd在集合std::set中的排序方式
     * Node内部类：class ce::Node::EdgeEndCompare
     */
    class EdgeEndCompare{
    public:
        bool operator()(const EdgeEnd& left, const EdgeEnd& right){
            if(left.GetNode().Index() == right.GetNode().Index()){
                if(left.GetSrcIndex() == right.GetSrcIndex())
                    return left.GetDstIndex() < right.GetDstIndex();
                else
                    return left.GetSrcIndex() < right.GetSrcIndex();
            }
            return left.GetNode().Index() < right.GetNode().Index();
        }
    };

    using EdgeEndSet = std::set<EdgeEnd, EdgeEndCompare>;
    using EdgeEndIterator = EdgeEndSet::const_iterator;

    /**
     * @brief 定义本节点的相关输入输出边的关系
     * Node内部类：class ce::Node::Relationships
     */
    class Relationships{
    public:
        void Clear(){
            input_edges.clear();
            output_edges.clear();
            control_inputs.clear();
        }

        EdgeEndSet input_edges, output_edges;
        std::set<std::string> control_inputs;
    };

private:
    NodeIndex index_ = std::numeric_limits<NodeIndex>::max();
    Relationships relationships_;
};
} // namespace ce
