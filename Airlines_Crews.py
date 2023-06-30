# python3
import copy
import queue

class solve_matching:
    def TakeInput(self):
        n, m = map(int, input().split())
        matrix = [list(map(int, input().split())) for i in range(n)]
        return matrix
    def WriteResult(self, matching):
        l = [str(-1 if x == -1 else x + 1) for x in matching]
        print(' '.join(l))
    def SearchMatching(self, matrix):
        n = len(matrix)
        m = len(matrix[0])
        match = [-1] * n
        IsBusy = [False] * m
        def bfs():
            IsVisitedNode = set()
            q = queue.Queue()
            q.put((1, None))
            IsVisitedNode.add((1, None))
            Way = []
            TrackParent = dict()
            while not q.empty():
                PresentNode = q.get()
                if 1 == PresentNode[0]: # Source
                    for i in range(n):
                        if -1 == match[i]:
                            IsVisitedNode.add((2, i))
                            TrackParent[(2, i)] = (1, None)
                            q.put((2, i))
                elif 2 == PresentNode[0]: # Flights
                    i = PresentNode[1]
                    for j in range(m):
                        if 1 == matrix[i][j] and j != match[i] and not (3, j) in IsVisitedNode:
                            IsVisitedNode.add((3, j))
                            TrackParent[(3, j)] = PresentNode
                            q.put((3, j))
                elif 3 == PresentNode[0]:
                    j = PresentNode[1]
                    if not IsBusy[j]:
                        EarlierNode = PresentNode
                        PresentNode = (4, j)
                        while True:
                            Way.insert(0, (EarlierNode, PresentNode))
                            if 1 == EarlierNode[0]:
                                break
                            PresentNode = EarlierNode
                            EarlierNode = TrackParent[PresentNode]
                        for e in Way:
                            if 2 == e[0][0]:
                                match[e[0][1]] = e[1][1]
                            elif 3 == e[0][0] and 4 == e[1][0]:
                                IsBusy[e[1][1]] = True
                        #print(Way)
                        return True # There is a Way
                    else:
                        for i in range(n):
                            if j == match[i] and not (2, i) in IsVisitedNode:
                                IsVisitedNode.add((2, i))
                                TrackParent[(2, i)] = PresentNode
                                q.put((2, i))
            return False # There isn't a Way

        while bfs():
            continue
        return match
    def solve(self):
        matrix = self.TakeInput()
        matching = self.SearchMatching(matrix)
        self.WriteResult(matching)

if __name__ == '__main__':
    max_matching = solve_matching()
    max_matching.solve()