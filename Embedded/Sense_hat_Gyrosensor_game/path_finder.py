'''
map = [
    [O, X, O, O, O, O, O, O],
    [O, X, X, X, X, O, X, O],
    [O, O, O, O, O, O, O, O],
    [O, X, X, X, X, O, X, O],
    [O, O, X, O, O, O, X, O],
    [O, O, X, O, X, X, X, O],
    [O, X, X, O, O, O, O, O],
    [O, O, O, O, X, X, X, O]]
'''

map = [
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 0]

dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]
start = (0, 0)
goal = (7, 7)

def getPath(map, y, x):
    visited = [[0 for i in range(8)] for j in range(8)]
    queue = [[(y, x)]]
    visited[y][x] = True
    
    while len(queue):
        now = queue.pop(0)
        
        for d in range(4):
            ny = now[-1][0] + dy[d]
            nx = now[-1][1] + dx[d]
            if(ny < 0 or ny > 7 or nx < 0 or nx > 7): continue
            if(map[ny*8+nx] == 1): continue
            if(visited[ny][nx]): continue
            visited[ny][nx] = True
            if(ny == goal[0] and nx == goal[1]):
                now.append(goal)
                return now
            newpath = now.copy()
            newpath.append((ny, nx))
            queue.append(newpath)
            
    return []

def showPath(map, y, x):
    newmap = map.copy()
    path = getPath(newmap, y, x)
    for pos in path:
        newmap[pos[0]*8+pos[1]] = 9
            
    return newmap