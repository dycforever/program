# -*- coding: utf-8 -*-

import sys
import math
import copy

class UnlappedSolution(object):
    def find_sub_str(self, s, start, target):
        for i in range(start, len(s)):
            sv = s[i]
            for j in range(i+1, len(s)):
                sv += s[j]
                if target == sv:
                    return i, j
        return -1, -1

    def func(self, s, target):
        """
        :type s: str
        :rtype: str
        """
        for i in range(len(s)):
            sv = s[i]
            for j in range(i+1, len(s)):
                sv += s[j]
                if target == sv:
                    start2, end2 = self.find_sub_str(s, j+1, target)
                    if start2 != -1:
                        return i, j, start2, end2
        return None

s = UnlappedSolution()
#print(s.func([1,3,4,6,5,3], 8))

class The132Solution(object):
    def func(self, s):
        if len(s) < 3:
            return False
        max_v = max(s)

        max_idx_set = []
        for idx, v in enumerate(s):
            if v == max_v:
                max_idx_set.append(idx)

        for idx in max_idx_set:
            if idx == 0:
                return self.func(s[1:])
            if idx == len(s)-1:
                return self.func(s[:-1])
            min_left = min(s[0:idx])
            max_right =  max(s[idx+1:])
            if min_left < max_v and max_right < max_v and max_right > min_left:
                return True
            if self.func(s[0:idx]):
                return True
            else:
                return self.func(s[idx+1:])

s = The132Solution()
#print s.func([1,3,2])
#print s.func([1,2,3, 5])
#print s.func([3,1,4, 2])
# TODO
#print s.func([-2,1,2,-2,1,2])


class MaxRingSolution(object):
    def func(self, s):
        max_single = max(s)
        max_for_now = -99999
        all_sum = sum(s)
        for start in range(len(s)):
            cur_sum = s[start]
            for i in range(1, len(s)-1):
                idx = start + i
                if idx >= len(s):
                    idx -= len(s)
                cur_sum += s[idx]
                max_for_now = max(cur_sum, max_for_now)
        return max(max_single, max(all_sum, max_for_now))

#s = MaxRingSolution()
#print(s.func([1,-2,3,-2]))
#print(s.func([5,-3,5]))
#print(s.func([3,-1,2,-1]))

class DupNumSolution(object):
    def func(self, s, k, t):
        if len(s) == 1:
            return False
        for start in range(len(s) - 1):
            for cur_len in range(1, min(k+1, len(s) - start)):
                diff = abs(s[start] - s[start + cur_len])
                if diff <= abs(t):
                    return True
        return False

#s = DupNumSolution()
#print(s.func([1,2,3,1], 3, 0))
#print(s.func([1,0,1,1], 1, 2))
#print(s.func([1,5,9,1,5,9], 2, 3))

## [start, end)
## s[start] == target
## end >= target 或者 OOB
def move_forward(s, start, end, target):
    while True:
        if start == end:
            return start
        idx = start + (end-start)//2
        if s[idx] == target:
            start = idx+1
            continue
        else:   # s[idx] > target
            end = idx
            continue

## [start, end]
def move_backward(s, start, end, target):
    if s[start] == target:
        return start
    while True:
        if start == end:
            return start
        idx = start + (end-start)//2
        if s[idx] == target:
            end = idx
        else:  # s[idx] < target
            start = idx+1

def bin_search(s, target, is_lower_bound=True):
    start = 0
    end = len(s)
    while True:
        if start == end:
            return start
        i = start + (end-start)//2
        if s[i] < target:
            start = i+1
            if start == len(s):
                return start
            continue
        elif s[i] > target:
            end = i
            continue
        else:
            if i == 0:
                return i
            if is_lower_bound:
                return move_backward(s, start, i, target)
            else:
                return move_forward(s, i, end, target)

### upper bound
#assert bin_search([0,1,1,1,1,1,1], 1, False) == 7
#assert bin_search([1,2,5,5,5,6,7], 6, False) == 6
#assert bin_search([1], 6, False) == 1
#assert bin_search([7], 6, False) == 0
#
### lower bound
#assert bin_search([0,1,1,1,1,1,1,], 1) == 1
#assert bin_search([1,2,5,5,5,6,7], 6) == 5
#assert bin_search([1], 6) == 1
#assert bin_search([7], 6) == 0
#print("all done")

class TripleSumSolution(object):
    def count_distinct(self, s, cnt_map, target):
        distinct_pair = set()
        for middle in set(s):
            new_target = target - middle
            first_part = []
            second_part = []
            for n in sorted(s):
                if n < middle:
                    first_part.append(n)
                elif n > middle:
                    second_part.append(n)
            ptr_i = 0
            ptr_j = len(second_part) - 1
            while ptr_i < len(first_part) and ptr_j >= 0:
                sum_val = first_part[ptr_i] + second_part[ptr_j]
                if sum_val == new_target:
                    distinct_pair.add((first_part[ptr_i], middle, second_part[ptr_j]))
                    ptr_i += 1
                    ptr_j -= 1
                elif sum_val < new_target:
                    ptr_i += 1
                else:
                    ptr_j -= 1
        total_cnt = 0
        for p in distinct_pair:
            total_cnt += cnt_map[p[0]] * cnt_map[p[1]] * cnt_map[p[2]]
        return total_cnt

    def cn2(self, n):
        return n*(n-1)//2

    def cn3(self, n):
        return n*(n-1)*(n-2)//3

    def count_double(self, s, cnt_map, target):
        visited = set()
        double_pair = []
        ret = 0
        for k, v in cnt_map.items():
            other = target - 2*k
            if (k, other) in visited or (other, k) in visited:
                continue
            if v >= 2 and other in cnt_map:
                double_pair.append((k, other))
        for pair in double_pair:
            ret += self.cn2(cnt_map[pair[0]]) * cnt_map[pair[1]]
        return ret

    def count_triple(self, s, cnt_map, target):
        if target % 3 != 0:
            return 0
        v = target // 3
        if v in cnt_map and cnt_map[v] >= 3:
            return self.cn3(v)

    def func(self, s, target):
        if len(s) < 3:
            return False

        cnt_map = {}
        for n in s:
            if n not in cnt_map:
                cnt_map[n] = 0
            cnt_map[n] += 1

        total_cnt = 0
        total_cnt += self.count_distinct(s, cnt_map, target)
        total_cnt += self.count_double(s, cnt_map, target)
        total_cnt += self.count_triple(s, cnt_map, target)
        return total_cnt

s = TripleSumSolution()
#print(s.func([1,1, 2,2, 3,3, 4,4, 5,5], 8))
#print s.func([1,1,2,2,3,3,4,4,5,5], 8)

class MaxSquareSolution(object):
    def func(self, row_size, column_size, rows, columns):
        rows.append(row_size)
        rows.append(0)
        columns.append(column_size)
        columns.append(0)

        rows = sorted(rows)
        columns = sorted(columns)
        max_row_diff = 0
        max_column_diff = 0
        for i in range(len(rows) - 1):
            max_row_diff = max(max_row_diff, rows[i+1] - rows[i])

        for i in range(len(columns) - 1):
            max_column_diff = max(max_column_diff, columns[i+1] - columns[i])

        return max_row_diff * max_column_diff

#s = MaxSquareSolution()
#print(s.func([1,2,4], [1,3], 5, 4))
#print(s.func([3,1], [1], 5, 4))
#print(s.func([3], [3], 5, 4))

class SwapInStringSolution(object):
    def apply(self, stat, op):
        new_stat = list(stat)
        tmp = stat[op[0]]
        new_stat[op[0]] = new_stat[op[1]]
        new_stat[op[1]] = tmp
        return "".join(new_stat)

    def neighbors(self, cur, ops, visited):
        ret = []
        for op in ops:
            new_stat = self.apply(cur, op)
            if new_stat not in visited:
                visited.add(new_stat)
                ret.append(new_stat)
        return ret

    def func(self, s, ops):
        visited = set()
        candidates = [s]
        while len(candidates) > 0:
            cur = candidates[0]
            candidates = candidates[1:]
            visited.add(cur)
            for n in self.neighbors(cur, ops, visited):
                candidates.append(n)
        return min(visited)
#s = SwapInStringSolution()
#assert s.func("dcab", [[0,3], [1,2]]) == "bacd"
#assert s.func("dcab", [[0,3], [1,2], [0,2]]) == "abcd"
#assert s.func("cba", [[0,1], [1,2]]) == "abc"
#check 超时了

class SumOfMinSubSeqSolution(object):
    def func(self, s):
        ret = 0
        for start in range(len(s)):
            cur_min = s[start]
            ret += cur_min
            for offset in range(1, len(s) - start):
                cur_min = min(cur_min, s[start + offset])
                ret += cur_min
        return ret % (1e9 + 7)
#s = SumOfMinSubSeqSolution()
#assert s.func([3,1,2,4]) == 17
#check 超时


class MinDiffSolution(object):
    def func(self, s, k):
        if len(s) == 1:
            return 0
        s = sorted(s)
        min_diff = s[-1] - s[0]
        min_val = sys.float_info.max
        max_val = sys.float_info.min
        for i in range(0, len(s) - 1):
            min_val = min(s[0] + k, s[i+1] - k)
            max_val = max(s[-1] - k, s[i] + k)
            min_diff = min(min_diff, abs(min_val - max_val))
        return min_diff

s = MinDiffSolution()
#print s.func([2,7,2], 1)
#assert s.func([1], 0) == 0
#assert s.func([0, 10], 2) == 6
#assert s.func([1, 3, 6], 3) == 3

class List(object):
    class Node(object):
        def __init__(self, v, prev, next):
            self.value = v
            self.next = next
            self.prev = prev

    def __init__(self):
        self.root = None
        self.tail = None
        self.size = 0

    def add(self, pos, value):
        ptr = self.root
        if pos == 0:
            new_node = self.Node(value, None, self.root)
            self.root = new_node
        else:
            for _ in range(pos):
                ptr = ptr.next
            new_node = self.Node(value, ptr, ptr.next)
            if ptr.next is not None:
                ptr.next.prev= new_node
            ptr.next = new_node
        if new_node.next is None:
            self.tail = new_node
        self.size += 1

    def append(self, value):
        if self.tail is None:
            self.size += 1
            return self.add(0, value)
        else:
            new_node = self.Node(value, self.tail, None)
            self.tail.next = new_node
            self.tail = new_node
            self.size += 1
            return True

    def showAll(self):
        ret = []
        ptr = self.root
        while ptr is not None:
            ret.append(ptr.value)
            ptr = ptr.next
        return ret

#l = List()
#l.append(1)
#l.append(3)
#print(l.showAll())


class Tree(object):
    class Node(object):
        def __init__(self, v):
            self.val = v
            self.left= None
            self.right = None

        def __str__(self):
            return str(self.val)

    def __init__(self, s):
        self.id_to_nodes = {}
        for idx, n in enumerate(s):
            node_id = idx + 1
            parent_id = node_id // 2
            if n == "null":
                continue
            node = self.Node(int(n))
            self.id_to_nodes[node_id] = node
            if node_id != 1:
                parent = self.id_to_nodes[parent_id]
                if node_id % 2 == 0:
                    parent.left= node
                else:
                    parent.right = node
        self.root = self.id_to_nodes[1]

    def iterate(self):
        ret = []
        queue = [self.root]
        while len(queue) > 0:
            n = queue[0]
            ret.append(n.val)
            queue = queue[1:]
            if n.left is not None:
                queue.append(n.left)
            if n.right is not None:
                queue.append(n.right)
        return ret

    def _is_valid_bin_search_tree(self, node):
        left_min = left_max = sys.float_info.max
        right_min = right_max = sys.float_info.min
        if node.left is not None:
            left_valid, left_min, left_max = self._is_valid_bin_search_tree(node.left)
            if not left_valid:
                return False, None, None
            if left_max >= node.val:
                return False, None, None

        if node.right is not None:
            right_valid, right_min, right_max = self._is_valid_bin_search_tree(node.right)
            print right_valid, right_min, right_max
            if not right_valid:
                return False, None, None
            if right_min <= node.val:
                return False, None, None
        if node.left is not None:
            min_v = left_min
        else:
            min_v = node.val

        if node.right is not None:
            max_v = right_max
        else:
            max_v = node.val
        return True, min_v, max_v

    def is_valid_bin_search_tree(self):
        ret, _, _ = self._is_valid_bin_search_tree(self.root)
        return ret

t = Tree("2,1,3".split(","))
t = Tree("0, -1".split(","))
#print t.iterate()
#print(t.is_valid_bin_search_tree())
#t = Tree("5,1,4,null,null,3,6".split(","))
#print(t.is_valid_bin_search_tree())
#
#print("all done")

class ReorderToHuiwenSolution(object):
    def __init__(self, s):
        self.s = s

    def func(self, queries):
        ret = []
        for start, end, k in queries:
            ret.append(self._func(start, end, k))
        return ret

    def _func(self, start, end, k):
        if end - start == 0:
            return True
        if (end - start + 1) % 2 == 1:
            is_odd = True
        else:
            is_odd = False
        s = copy.deepcopy(self.s[start:end+1])
        count_map = {}
        for c in s:
            if c not in count_map:
                count_map[c] = 1
            elif count_map[c] == 1:
                count_map[c] = 0
            else:
                count_map[c] = 1
        odd_set = set()
        for c, v in count_map.items():
            if v == 1:
                odd_set.add(c)
        upper_case_cnt = 0
        for c in odd_set:
            if c.islower():
                continue
            upper_case_cnt += 1
        if upper_case_cnt > k:
            return False
        if is_odd:
            if len(odd_set) -1 > (2*k):
                return False
        else:
            if len(odd_set) > 2*k:
                return False
        return True
#s = ReorderToHuiwenSolution("abcda")
#queries = [ [3,3,0], [1,2,0], [0,3,1], [0,3,2], [0,4,1] ]
#print(s.func(queries))

class DeleteCommentsSolution(object):
    def __init__(self):
        self.state = 1
        ## 1 normal
        ## 2 block comment

    def process_line(self, line):
        if self.state == 2:
            pos = line.find("*/")
            if pos == -1:
                return ""
            line = line[pos+2:]
            self.state = 1
            return self.process_line(line)

        line_cmt_pos = line.find("//")
        block_cmt_pos = line.find("/*")
        if line_cmt_pos == -1 and block_cmt_pos == -1:
            return line
        elif (line_cmt_pos != -1 and block_cmt_pos == -1) or (
            line_cmt_pos != -1 and block_cmt_pos != -1 and line_cmt_pos < block_cmt_pos
        ):
            line = line[0:line_cmt_pos]
            return line
        elif (block_cmt_pos != -1 and line_cmt_pos == -1) or (
            line_cmt_pos != -1 and block_cmt_pos != -1 and block_cmt_pos < line_cmt_pos
        ):
            self.state = 2
            before_cmt = line[0:block_cmt_pos]
            block_end_pos = line.find("*/")
            if block_end_pos == -1:
                line = before_cmt
            else:
                self.state = 1
                after_cmt = line[block_end_pos+2:]
                line =  before_cmt + after_cmt
            return line
        assert False

    def func(self, code):
        ret = []
        for line in code:
            line = self.process_line(line)
            if len(line) > 0:
                ret.append(line)
        return ret

s = DeleteCommentsSolution()
code = []
code.append("/*xx*/")
code.append("a/*xx*/b")
code.append("c/*x")
code.append("x*/d")
code.append("e//d")
code.append("///*f")
code.append("/*f")
code.append("*/f//cc")
#check:
#code.extend(["a/*comment", "line", "more_comment*/b"])
#print(s.func(code))
class CircusSolution(object):
    def __init__(self):
        self.root = self.Node(sys.float_info.max, sys.float_info.max)

    class Node(object):
        def __init__(self, h, w):
            self.branches = []
            self.h = h
            self.w = w

        def __str__(self):
            return "%s:%s" % (self.h, self.w)

    def less(self, n1, n2):
        if n1.h < n2.h and n1.w < n2.w:
            return True
        return False

    def insert_into(self, parent, node):
        is_new_branch = True
        for idx, c in enumerate(parent.branches):
            if self.less(node, c):
                is_new_branch = False
                self.insert_into(c, node)
            elif self.less(c, node):
                is_new_branch = False
                parent.branches[idx] = node
                node.branches.append(c)
        if is_new_branch:
            parent.branches.append(node)

    def max_deepth(self, node):
        if len(node.branches) == 0:
            return 1
        return 1 + max([self.max_deepth(b) for b in node.branches])

    def longest_queue(self):
        return self.max_deepth(self.root) - 1

    def func(self, heights, widths):
        for h, w in zip(heights, widths):
            node = self.Node(h, w)
            self.insert_into(self.root, node)

# s = CircusSolution()
# print s.longest_queue()
# h = [65, 70, 56, 75, 60, 68]
# w = [100, 150, 90, 190, 95, 110]
# s.func(h, w)
# print s.longest_queue()


class DijskraSolution(object):
    def __init__(self, s):
        self.edges = {}
        self.nodes = set()
        for edge in s:
            edge = edge.split(",")
            start = int(edge[0])
            end = int(edge[1])
            self.nodes.add(start)
            self.nodes.add(end)
            weight = float(edge[2])
            if start not in self.edges:
                self.edges[start] = {}
            if end not in self.edges[start]:
                self.edges[start][end] = {}
            else:
                print "duplicate:", start, end
                exit(1)
            self.edges[start][end] = weight

    def func(self, target):
        min_prob = {0:1}
        unvisited = self.nodes - set([0])
        while True:
            max_prob = 0
            choosen_end = None
            for start in min_prob.keys():
                if start not in self.edges:
                    continue

                for end in self.edges[start]:
                    if end in min_prob:
                        continue
                    if self.edges[start][end] > max_prob:
                        choosen_start = start
                        choosen_end = end

            if choosen_end == None:
                return 0

            if choosen_end == target:
                return min_prob[choosen_start] * self.edges[choosen_start][choosen_end]
            min_prob[choosen_end] = min_prob[choosen_start] * self.edges[choosen_start][choosen_end]



#g = [
#        "0,1,0.5",
#        "0,2,0.2",
#        "1,2,0.5",
#]
#g = [
#        "0,1,0.5",
#        "0,2,0.3",
#        "1,2,0.5",
#]
#g = [
#        "0,1,0.5",
#]
#s = DijskraSolution(g)
#print s.func(1)
#print s.func(2)

class OneEditSolution(object):
    def func(self, str1, str2):
        pos1 = 0
        pos2 = 0
        if abs(len(str1) - len(str2)) > 1:
            return False

        while pos1<len(str1) and pos2 < len(str2) and str1[pos1] == str2[pos2]:
            pos1 += 1
            pos2 += 1

        if pos1 == len(str1) or pos2 == len(str2):
            return True

        if str1[pos1+1:] == str2[pos2:] or str1[pos1:] == str2[pos2+1:] or str1[pos1+1:] == str2[pos2+1:]:
            return True

        return False

#s = OneEditSolution()
#print s.func("dyc", "dyc1")
#print s.func("dyc1", "dyc2")
#print s.func("dyc1", "dyc")
#print s.func("dcc", "dyc")
#print s.func("dcc2", "dyc")
#
#print s.func("pale", "ple")
#print s.func("pales", "pal")

class UniqFileNameSolution(object):
    def __init__(self):
        self.all_files = set()

    def func(self, flist):
        ret = []
        prev_cnt = {}
        for f_orig in flist:
            f_new = f_orig
            cnt = 0
            if f_orig in prev_cnt:
                cnt = prev_cnt[f_orig]
            while f_new in self.all_files:
                cnt += 1
                f_new = f_orig + "(%s)" % cnt
            prev_cnt[f_orig] = cnt
            ret.append(f_new)
            self.all_files.add(f_new)
        return ret

s = UniqFileNameSolution()
#names = ["wano", "wano", "wano", "wano"]
#names = ["kaido", "kaido(1)", "kaido(2)", "kaido(1)"]
#names = ["op", "op(1)", "op(2)", "op(3)", "op"]
#print s.func(names)

class InvalidTransactionSolution(object):
    class Transaction(object):
        def __init__(self, n, t, p, c):
            self.name = n
            self.time = t
            self.city = c
            self.price = p

        def __str__(self):
            return "%s  %s  %s  %s" % (
                    self.name, self.time, self.city, self.price)

    def __init__(self):
        pass

    def checklist(self, tlist):
        start = 0
        end = 0
        record_map = {}
        ret = set()

        while end < len(tlist):
            t_end = tlist[end]
            if t_end.city not in record_map:
                record_map[t_end.city] = 0
            record_map[t_end.city] += 1
            end += 1

            t_start = tlist[start]
            while start < end and t_end.time - t_start.time > 60:
                if record_map[t_start.city] == 1:
                    del record_map[t_start.city]
                else:
                    record_map[t_start.city] -= 1
                start += 1
            if len(record_map) > 1:
                for i in range(start, end):
                    ret.add(i)
        return list(tlist[i] for i in ret)

    # name, time, price, city
    def func(self, tlist):
        tmap = {}
        ret = []
        for t in tlist:
            if t.price > 1000:
                ret.append(t)
                continue
            if t.name not in tmap:
                tmap[t.name] = []
            tmap[t.name].append(t)

        for name in tmap.keys():
            tmap[name] = sorted(tmap[name], key=lambda t:t.time)

        for name, tlist in tmap.items():
            ret.extend(self.checklist(tlist))
        return ret

#s = InvalidTransactionSolution()
#tlist = [InvalidTransactionSolution.Transaction("alice", 20, 800, "mtv"), InvalidTransactionSolution.Transaction("alice", 50, 100, "beijing")]
#for t in s.func(tlist):
#    print t, "|",
#print ""
#
#tlist = [InvalidTransactionSolution.Transaction("alice", 20, 800, "mtv"), InvalidTransactionSolution.Transaction("alice", 50, 1200, "beijing")]
#for t in s.func(tlist):
#    print t, "|",
#print ""
#
#tlist = [InvalidTransactionSolution.Transaction("alice", 20, 800, "mtv"), InvalidTransactionSolution.Transaction("bob", 50, 1200, "beijing")]
#for t in s.func(tlist):
#    print t, "|",
#print ""

class PracticeSolution(object):
    def __init__(self):
        pass

    def valid(self, s, limit, m):
        day_time = 0
        day_time_max = 0
        ret = []
        for t in s:
            if day_time + t <= limit:
                day_time += t
                day_time_max = max(day_time_max, t)
            else:
                ret.append(day_time - day_time_max)
                day_time = t
                day_time_max = t
        if day_time > 0:
            ret.append(day_time)
        return limit >= max(s)

    def func(self, s, m):
        l = 0
        r = sum(s)
        while True:
            if l+1 == r:
                return r
            middle = l + (r-l)//2
            if self.valid(s, middle, m):
                r = middle
            else:
                l = middle

#s = PracticeSolution()
#print s.func([1,2,3,4,7], 1)

class WordPathInDictSolution(object):
    def add_to_graph(self, g, word):
        if word in g:
            assert False
        g[word] = []
        for w in g.keys():
            if self.diff_of_1char(w, word):
                g[word].append(w)
                g[w].append(word)
        return False


    def generate_trace(self, trace, start, target):
        ret = [target]
        src = trace[target]
        while src != start:
            ret.insert(0, src)
            src = trace[src]
        return ret


    def diff_of_1char(self, s1, s2):
        if len(s1) != len(s2):
            return False
        diff_cnt = 0
        for idx in range(len(s1)):
            if s1[idx] != s2[idx]:
                diff_cnt += 1
        return diff_cnt == 1


    def travel(self, g, start, target):
        trace = {}
        visited = set()
        candidates = [start]
        while len(candidates) > 0:
            cur = candidates[0]
            visited.add(cur)
            if cur == target:
                return self.generate_trace(trace, start, cur)

            candidates = candidates[1:]
            for neighbor in g[cur]:
                if neighbor in visited:
                    continue
                trace[neighbor] = cur
                candidates.append(neighbor)
        return None

    def func(self, word_set, start, target):
        if target not in word_set:
            return []
        g = {start : []}

        for word in word_set:
            if word == start:
                continue
            self.add_to_graph(g, word)

        ret = self.travel(g, start, target)
        return ret


#s = WordPathInDictSolution()
#start = "hit"
#target = "cog"
#word_set = ["hot", "dot", "dog", "lot", "log", "cog"]
#print s.func(word_set, start, target)
#
#word_set = ["hot", "dot", "dog", "lot"]
#print s.func(word_set, start, target)



class LongestAscendingSubstrSolution(object):
    def __init__(self):
        pass

    class Record(object):
        def __init__(self, p, l):
            self.prev = p
            self.length = l

    def func(self, s):
        records = []
        for n_idx, n in enumerate(s):
            max_prev_length = 0
            max_prev_idx = -1
            for idx in range(n_idx):
                if n <= s[idx]:
                    continue
                if records[idx].length > max_prev_length:
                    max_prev_length = records[idx].length
                    max_prev_idx = idx

            records.append(self.Record(max_prev_idx, max_prev_length + 1))

        max_length = 0
        max_idx = 0
        for idx, r in enumerate(records):
            if r.length > max_length:
                max_length = r.length
                max_idx = idx
        ret = []
        idx = max_idx
        ret.append(s[idx])
        while records[idx].prev != -1:
            ret.insert(0, s[records[idx].prev])
            idx = records[idx].prev

        return ret

#s = LongestAscendingSubstrSolution()
#print s.func([10, 9, 2, 5, 3, 7, 101, 18])


class LongestAscendingSubstrSolution2(object):
    def __init__(self):
        pass

    class Record(object):
        def __init__(self, p, l):
            self.prev = p
            self.length = l

    def generate_seq(self, s, records, pos_list):
        if len(pos_list) == 0:
            return [[]]

        ret = []
        for pos in pos_list:
            record = records[pos]

            for seq in self.generate_seq(s, records, record.prev):
                seq.append(s[pos])
                ret.append(seq)
        return ret


    def func(self, s):
        records = []
        for n_idx, n in enumerate(s):
            max_prev_length = 0
            max_prev_idx = []
            for idx in range(n_idx):
                if n <= s[idx]:
                    continue
                if records[idx].length > max_prev_length:
                    max_prev_length = records[idx].length
                    max_prev_idx = [idx]
                elif records[idx].length == max_prev_length:
                    max_prev_idx.append(idx)

            records.append(self.Record(max_prev_idx, max_prev_length + 1))

        max_length = 0
        max_idx = []
        for idx, r in enumerate(records):
            if r.length > max_length:
                max_length = r.length
                max_idx = [idx]
            elif r.length == max_length:
                max_idx.append(idx)

        return self.generate_seq(s, records, max_idx)

#s = LongestAscendingSubstrSolution2()
#print s.func([10, 9, 2, 5, 3, 7, 101, 18])

class MaxSubstrSumSolution(object):
    class Record(object):
        def __init__(self, m):
            self.m = m

    def func(self, s):
        dp_records = []
        for n_idx, n in enumerate(s):
            max_sum = 0
            for idx in range(n_idx):
                if n + dp_records[idx].m > max_sum:
                    max_sum = n + dp_records[idx].m
            record = self.Record(max_sum)
            dp_records.append(record)

class ShuDuSolution(object):
    def __init__(self):
        self.size = 9

    def padding(self, m):
        for r in range(self.size):
            if len(m[r]) < self.size:
                m[r].extend([0] * (self.size - len(m[r])))

    def find_blank(self, m):
        ret = []
        for i in range(self.size):
            for j in range(self.size):
                if m[i][j] == 0:
                    ret.append((i, j))
        return ret

    def all_available(self, m, current_pos):
        row = current_pos[0]
        column = current_pos[1]
        num_set = set()
        for rid in range(self.size):
            num_set.add(m[rid][column])
        for cid in range(self.size):
            num_set.add(m[row][cid])

        blocksize = 3
        brid = row//blocksize
        bcid = column//blocksize
        for rid in range(blocksize):
            for cid in range(blocksize):
                num_set.add(m[brid*blocksize + rid][bcid * blocksize + cid])

        ret = []
        for i in range(self.size + 1):
            if i not in num_set:
                ret.append(i)
        return ret

    def proceed(self, m, all_pos):
        if len(all_pos) == 0:
            return True
        current_pos = all_pos[0]
        available = self.all_available(m, current_pos)
        if len(available) == 0:
            return False

        for action in available:
            m[current_pos[0]][current_pos[1]] = action
            if self.proceed(m, all_pos[1:]):
                return True
            m[current_pos[0]][current_pos[1]] = 0
        return False

    def func(self, matrix):
        self.padding(matrix)
        all_pos = self.find_blank(matrix)
        if self.proceed(matrix, all_pos):
            print matrix
        else:
            print "invalid"


#s = ShuDuSolution()
#m = [
#    [5,3,0,0,7],
#    [6,0,0,1,9,5],
#    [0,9,8,0,0,0,0,6],
#    [8,0,0,0,6,0,0,0,3],
#    [4,0,0,8,0,3,0,0,1],
#    [7,0,0,0,2,0,0,0,6],
#    [0,6,0,0,0,0,2,8],
#    [0,0,0,4,1,9,0,0,5],
#    [0,0,0,0,8,0,0,7,9],
#]
#s.func(m)


class NQueenSolution(object):
    def __init__(self):
        pass

    def find_all_available(self, stat):
        next_row = len(stat)
        ret = []
        for column in range(self.n):
            avail = True
            for prev_row, prev_column in enumerate(stat):
               if column == prev_column:
                   avail = False
                   break
               if abs(column - prev_column) == abs(prev_row - next_row):
                   avail = False
                   break
            if avail:
                ret.append(column)
        return ret

    def proceed(self, stat):
        all_available = self.find_all_available(stat)
        if len(all_available) == 0:
            return 0
        ret = 0
        for pos in all_available:
            stat.append(pos)
            if len(stat) < self.n:
                ret += self.proceed(stat)
            else:
                ret += 1
            stat.pop()
        return ret


    def func(self, n):
        self.n = n
        stat = []
        return self.proceed(stat)

#s = NQueenSolution()
#for i in range(10):
#    print i+1, s.func(i+1)

class ArrayCutSolution(object):
    def __init__(self):
        pass

    def find_factors(self, n):
        i = 2
        ret = []
        root = math.sqrt(n)
        while i <= root:
            if n % i == 0:
                ret.append(i)
                ret.extend(self.find_factors(n//i))
                break
            i += 1
        if len(ret) == 0:
            ret.append(n)
        return ret

    ### [(35, 44), (55, 83)]
    def cut(self, s, factors, start, end):
        if start == end:
            return []
        if start == (end-1):
            return [(start, end-1)]
        min_len_seq = None
        i = end - 1
        ret = []
        while i >= start:
            common_factors = factors[i].intersection(factors[start])
            if i != start and len(common_factors) == 0:
                i -= 1
                continue
            ret.append((start, i))
            r = self.cut(s, factors, i+1, end)
            ret.extend(r)

            if min_len_seq is None or len(ret) < len(min_len_seq):
                min_len_seq = ret
            i -= 1
            ret = []
        #if min_len_seq is None:
        #    min_len_seq = []
        #    min_len_seq.append((start, start))
        #    min_len_seq.extend(self.cut(s, factors, start+1, end))
        return min_len_seq

    def func(self, s):
        factors = []
        for idx, n in enumerate(s):
            factors.append(set(self.find_factors(n)))

        return len(self.cut(s, factors, 0, len(s)))

    def dp(self, s, factors):
        f = [(1, 0, 0)]
        for i in range(1, len(s)):
            min_split = len(s)
            for j in range(0, i):
                common_factors = factors[i].intersection(factors[j])
                if len(common_factors) > 0:
                    if j == 0:
                        min_split = 1
                        start = j
                        end = i
                    else:
                        if min_split > f[j-1][0] + 1:
                            min_split = f[j-1][0] + 1
                            start = j
                            end = i
                else:
                    if min_split >= f[i-1][0] + 1:
                        min_split = f[i-1][0] + 1
                        start = i
                        end = i
            f.append((min_split, start, end))
        return f

    def func2(self, s):
        factors = []
        for idx, n in enumerate(s):
            factors.append(set(self.find_factors(n)))

        f = self.dp(s, factors)
        idx = len(s) - 1
        ret = []
        loop_cnt = 0
        #print f
        while True:
            #if f[idx][1] != f[idx][2]:
            ret.insert(0, (f[idx][1], f[idx][2]))
            if idx == 0:
                break
            idx = f[idx][1] - 1
            loop_cnt += 1
            if loop_cnt > 100:
                break
        #print ret
        #return len(ret)
        return f[-1][0]





s = ArrayCutSolution()
#print s.func([2,3,3,2,3,3])
#print s.func([2,3,5,7])
#print s.func2([2,3,5,7])
a = [782581,227,113147,13451,288053,684113,413579,917629,454021,827633,673787,514127,432001,507961,790051,164617,139759,315881,160681,235231,106627,135977,483811,570839,758699,549011,389227,21961,524347,24763,882247,932101,717559,124853,967919,968111,966439,967229,967739,968213,967171,966509,967397,967481,968111,967297,968311,967753,966677,968573,966527,966653,967319,967663,967931,968021,967961,968423,966727,967937,967699,966883,968017,968311,967781,966617,967937,967763,967459,966971,968567,968501,966991,966613,968557,966863,966619,966863,966727,967567,967061,966913,966631,968021,968003,968431,968291,969667,970667,971723,969011,972113,972373,969929,971491,970027,973031,982973,980491,985657]
print s.func(a)
print s.func2(a)

#print s.find_factors(980491)
#print s.find_factors(227)
