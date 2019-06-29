#pragma once
#ifndef __KDTREE_HPP
#define __KDTREE_HPP


#include <vector>
#include <algorithm>

#include <boost/multi_array.hpp>
#include <boost/array.hpp>

namespace kdtree {

	typedef boost::multi_array<float, 2>           KDTreeArray;//创建一个二维数组，数据是float类型
	typedef boost::const_multi_array_ref<float, 2> KDTreeROArray;//一个一维的数组，可以被看作常量的多维数组

	typedef struct {
		float lower, upper;
	} interval;

	//让编译器知道这是类名
	class KDTreeNode;//k-d树的节点
	class SearchRecord;//k-d树寻找最邻近点

	struct KDTreeResult {
	public:
		float dis;  // 最邻近点与查询点的距离  square distance
		int idx;    // 最邻近点的坐标  neighbor index
	};

	class KDTreeResultVector : public std::vector<KDTreeResult> {
		public:
			void push_element_and_heapify(KDTreeResult&);
			float replace_maxpri_elt_return_new_maxpri(KDTreeResult&);

			float max_value();
	};

	class KDTree {
	public:
		const KDTreeArray& the_data; //树中所包含的多维数据的一个参考数据，该数据没有存储底层，因此若要
		                              //改变该值的内容，需要重新分配存储底层


		const int N;          // 数据点的数量  
		int dim;             //  数据的维数
		bool sort_results;    // 排序结果 
		const bool rearrange; // 重新排序  

	public:

		KDTree(KDTreeArray& data_in, bool rearrange_in = true, int dim_in = -1);

		~KDTree();


	public:

		void n_nearest_brute_force(std::vector<float>& qv, int nn, KDTreeResultVector& result);

		void n_nearest(std::vector<float>& qv, int nn, KDTreeResultVector& result);

		void n_nearest_around_point(int idxin, int correltime, int nn,
			KDTreeResultVector& result);

		void r_nearest(std::vector<float>& qv, float r2, KDTreeResultVector& result);

		void r_nearest_around_point(int idxin, int correltime, float r2,
			KDTreeResultVector& result);

		int r_count(std::vector<float>& qv, float r2);

		int r_count_around_point(int idxin, int correltime, float r2);

		friend class KDTreeNode;
		friend class SearchRecord;

	private:

		KDTreeNode* root; // the root pointer

		const KDTreeArray* data;//要么指向the_data,要么指向rearranged_data

		std::vector<int> ind;

		KDTreeArray rearranged_data;//重排之后，数据的存储

		static const int bucketsize = 12;  // global constant.

	private:
		void set_data(KDTreeArray& din);
		void build_tree(); // 建k-d 树
		KDTreeNode* build_tree_for_range(int l, int u, KDTreeNode* parent);
		void select_on_coordinate(int c, int k, int l, int u);
		int select_on_coordinate_value(int c, float alpha, int l, int u);
		void spread_in_coordinate(int c, int l, int u, interval& interv);
	};

	class KDTreeNode {
	public:
		KDTreeNode(int dim);
		~KDTreeNode();

	private:
		friend class KDTree;  // allow kdtree to access private data

		int cut_dim; //根据哪个维度分割平面
		float cut_val, cut_val_left, cut_val_right;  //cut value
		int l, u;  // 对坐标范围内的值进行搜索

		std::vector<interval> box; // 包含所有点的盒子【最小值，最大值】

		KDTreeNode *left, *right;  // pointers to left and right nodes.

		void search(SearchRecord& sr);//用于搜索的递归内核例程

		bool box_in_search_range(SearchRecord& sr);

		void check_query_in_bound(SearchRecord& sr); // debugging only

		void process_terminal_node(SearchRecord& sr);
		void process_terminal_node_fixedball(SearchRecord& sr);
	};

} // namespace kdtree

#endif
