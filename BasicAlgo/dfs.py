from collections import defaultdict

class Graph:
    def __init__(self,_NumVerts):
        self.NumVerts = _NumVerts
        self.graph = defaultdict(list)
    def Connect(self,ID,v):
        self.graph[ID].append(v)
    def GetPath(self, ID, FinalID, visited, path):
        visited[ID]= True
        path.append(ID)
        if ID == FinalID:
            print (path)
        else:
            for Vertex in self.graph[ID]:
                if visited[Vertex] == False:
                    self.GetPath(Vertex, FinalID, visited, path)
        path.pop()
        visited[ID]= False
    def printAllPaths(self,start, FinalID):
        visited = [False]*(self.NumVerts)
        path = []
        self.GetPath(start, FinalID,visited, path)

gaphIns = Graph(4)
gaphIns.Connect(0, 1)
gaphIns.Connect(0, 2)
gaphIns.Connect(0, 3)
gaphIns.Connect(2, 0)
gaphIns.Connect(2, 1)
gaphIns.Connect(1, 3)
  
start = 0
end = 3
print ("List of paths from " + str(start) + " to " + str(end) + ": ")
gaphIns.printAllPaths(start, end)