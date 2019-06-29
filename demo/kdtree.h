#pragma once
#ifndef __KDTREE_HPP
#define __KDTREE_HPP


#include <vector>
#include <algorithm>

#include <boost/multi_array.hpp>
#include <boost/array.hpp>

namespace kdtree {

	typedef boost::multi_array<float, 2>           KDTreeArray;//����һ����ά���飬������float����
	typedef boost::const_multi_array_ref<float, 2> KDTreeROArray;//һ��һά�����飬���Ա����������Ķ�ά����

	typedef struct {
		float lower, upper;
	} interval;

	//�ñ�����֪����������
	class KDTreeNode;//k-d���Ľڵ�
	class SearchRecord;//k-d��Ѱ�����ڽ���

	struct KDTreeResult {
	public:
		float dis;  // ���ڽ������ѯ��ľ���  square distance
		int idx;    // ���ڽ��������  neighbor index
	};

	class KDTreeResultVector : public std::vector<KDTreeResult> {
		public:
			void push_element_and_heapify(KDTreeResult&);
			float replace_maxpri_elt_return_new_maxpri(KDTreeResult&);

			float max_value();
	};

	class KDTree {
	public:
		const KDTreeArray& the_data; //�����������Ķ�ά���ݵ�һ���ο����ݣ�������û�д洢�ײ㣬�����Ҫ
		                              //�ı��ֵ�����ݣ���Ҫ���·���洢�ײ�


		const int N;          // ���ݵ������  
		int dim;             //  ���ݵ�ά��
		bool sort_results;    // ������ 
		const bool rearrange; // ��������  

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

		const KDTreeArray* data;//Ҫôָ��the_data,Ҫôָ��rearranged_data

		std::vector<int> ind;

		KDTreeArray rearranged_data;//����֮�����ݵĴ洢

		static const int bucketsize = 12;  // global constant.

	private:
		void set_data(KDTreeArray& din);
		void build_tree(); // ��k-d ��
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

		int cut_dim; //�����ĸ�ά�ȷָ�ƽ��
		float cut_val, cut_val_left, cut_val_right;  //cut value
		int l, u;  // �����귶Χ�ڵ�ֵ��������

		std::vector<interval> box; // �������е�ĺ��ӡ���Сֵ�����ֵ��

		KDTreeNode *left, *right;  // pointers to left and right nodes.

		void search(SearchRecord& sr);//���������ĵݹ��ں�����

		bool box_in_search_range(SearchRecord& sr);

		void check_query_in_bound(SearchRecord& sr); // debugging only

		void process_terminal_node(SearchRecord& sr);
		void process_terminal_node_fixedball(SearchRecord& sr);
	};

} // namespace kdtree

#endif
