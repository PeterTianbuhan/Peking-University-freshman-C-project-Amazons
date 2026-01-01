#include <iostream>     // cin, cout, endl
#include <iomanip>      // setw 画棋盘
#include <vector>       // vector 
#include <string>       // string
#include <algorithm>    // max, min, sort
#include <cmath>        // abs, sqrt
#include <cstdlib>      // system("cls"), rand
#include <ctime>        // time 随机数种子
#include <fstream>      // fstream 文件读写
#include <cstring>      // memset, memcpy
#include <queue>        // queue 用于 BFS
#include <tuple>       // tuple 用于存储移动信息

using namespace std;
using Move = tuple<int,int,int,int,int,int>;

class Amazons
{
    private:
        static const int N = 10;          // 棋盘大小
        int board[N][N];                 // 棋盘数组
        int currentPlayer=1;              // 当前玩家
        int humanPlayer;               // 人类玩家编号
    public:
        Amazons()
        {
            initializeBoard();
            currentPlayer = 1; // 玩家1先手
        }                      // 构造函数
        void initializeBoard()
        {
            memset(board, 0, sizeof(board));
            // 初始化棋盘
            board[0][3] = 1; board[0][6] = 1; board[9][3] = 2; board[9][6] = 2; 
            board[3][0] = 1; board[3][9] = 1; board[6][0] = 2; board[6][9] = 2;
            //放置8个皇后
        }         // 初始化棋盘
        void displayBoard()
        {
            system("cls"); // 清屏
            cout << "  ";
            for (int i = 0; i < N; ++i)
                cout << setw(2) << i;
            cout << endl;
            for (int i = 0; i < N; ++i)
            {
                cout << setw(2) << i;
                for (int j = 0; j < N; ++j)
                {
                    if (board[i][j] == 0)
                        cout << " .";
                    else if (board[i][j] == 1)
                        cout << " A"; // 玩家1的皇后
                    else if (board[i][j] == 2)
                        cout << " B"; // 玩家2的皇后
                    else if (board[i][j] == -1)
                        cout << " X"; // 箭矢位置
                }
                cout << endl;
            }
        }          // 显示棋盘
        bool saveGame(string filename)
        {
            ofstream out(filename);
            if (!out) return false;
            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                {
                    out << board[i][j] << " ";
                }
                out << endl;
            }
            out << currentPlayer << endl;
            out << humanPlayer << endl;
            out.close();
            return true;
        }           // 保存游戏
        bool loadGame(string filename)
        {
            ifstream in(filename);
            if (!in) return false;
            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                {
                    in >> board[i][j];
                }
            }
            in >> currentPlayer;
            in >> humanPlayer;
            in.close();
            return true;
        }           // 加载游戏
        bool isValidMove(int x1, int y1, int x2, int y2)
        {
            if(board[x1][y1]!=currentPlayer) return false; // 只能移动自己的皇后
            if (x2 < 0 || x2 >= N || y2 < 0 || y2 >= N) return false; // 越界
            if(x1==x2 && y1==y2) return false; // 不能原地不动
            if (board[x2][y2] != 0) return false; // 目标位置不为空
            int dx = x2 - x1;
            int dy = y2 - y1;
            if (dx != 0) dx /= abs(dx);
            if (dy != 0) dy /= abs(dy);
            int cx = x1 + dx;
            int cy = y1 + dy;
            while (cx != x2 || cy != y2)
            {
                if (board[cx][cy] != 0) return false; // 路径上有障碍物
                cx += dx;
                cy += dy;
            }
            return true;
        }                // 检查移动是否合法
        void makeMove(int x1, int y1, int x2, int y2)
        {
            board[x2][y2] = board[x1][y1];
            board[x1][y1] = 0;
        }                   // 执行移动
        void shootArrow(int x2,int y2)
        {
            board[x2][y2] = -1; // 用-1表示箭矢位置
        }                  // 发射箭矢
        bool hasValidMoves(int player)
        {
            for (int x = 0; x < N; ++x)
            {
                for (int y = 0; y < N; ++y)
                {
                    if (board[x][y] == player)
                    {
                        // 检查该皇后所有可能的移动
                        for (int dx = -1; dx <= 1; ++dx)
                        {
                            for (int dy = -1; dy <= 1; ++dy)
                            {
                                if (dx == 0 && dy == 0) continue;
                                int nx = x + dx;
                                int ny = y + dy;
                                while (nx >= 0 && nx < N && ny >= 0 && ny < N && board[nx][ny] == 0)
                                {
                                    // 检查从(nx, ny)发射箭矢的所有可能位置
                                    for (int adx = -1; adx <= 1; ++adx)
                                    {
                                        for (int ady = -1; ady <= 1; ++ady)
                                        {
                                            if (adx == 0 && ady == 0) continue;
                                            int ax = nx + adx;
                                            int ay = ny + ady;
                                            while (ax >= 0 && ax < N && ay >= 0 && ay < N && board[ax][ay] == 0)
                                            {
                                                return true; // 找到一个合法移动
                                                ax += adx;
                                                ay += ady;
                                            }
                                        }
                                    }
                                    nx += dx;
                                    ny += dy;
                                }
                            }
                        }
                    }
                }
            }
            return false; // 没有合法移动
        } // 判断游戏是否结束
        void switchPlayer()
        {
            currentPlayer = 3 - currentPlayer;
        }            
        // 切换玩家
        int getCurrentPlayer()
        {
            return currentPlayer;
        }         // 获取当前玩家
        int gethumanplayer()
        {
            return humanPlayer;
        }    // 获取人类玩家编号
        void decidehumanplayer(int p)
        {
            humanPlayer=p;
        } // 设置人类玩家编号
        int calculateMobility(int currentBoard[N][N], int player)
        {
            int mobility = 0;
            int dirs[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
            
            for(int i = 0; i < N; i++) {
                for(int j = 0; j < N; j++) {
                    if(currentBoard[i][j] == player) {
                        // 对每个皇后，检查8个方向
                        for(int d = 0; d < 8; d++) {
                            int nx = i + dirs[d][0];
                            int ny = j + dirs[d][1];
                            while(nx >= 0 && nx < N && ny >= 0 && ny < N && currentBoard[nx][ny] == 0) {
                                mobility++;
                                nx += dirs[d][0];
                                ny += dirs[d][1];
                            }
                        }
                    }
                }
            }
            return mobility;
        }
        // Level 3 核心：计算独立区域的“确定性领地”分数
        int calculateRoomScore(int currentBoard[N][N], int player)
        {
            bool visited[N][N];
            memset(visited, 0, sizeof(visited));
            int mySecureTerritory = 0;
            int opSecureTerritory = 0;
            int opponent = 3 - player;
            
            // 遍历棋盘所有位置
            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                {
                    // 如果遇到障碍物(箭)或已访问过的点，跳过
                    if (currentBoard[i][j] == -1 || visited[i][j]) continue;

                    // --- 发现一个新的未访问区域，开始 Flood Fill (BFS) ---
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    visited[i][j] = true;

                    int emptyCount = 0;   // 该区域空位数
                    bool hasMe = false;   // 是否有我方棋子
                    bool hasOp = false;   // 是否有敌方棋子
                    
                    int dirs[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};

                    while (!q.empty())
                    {
                        auto [cx, cy] = q.front();
                        q.pop();

                        // 统计该位置的内容
                        if (currentBoard[cx][cy] == 0) emptyCount++;
                        else if (currentBoard[cx][cy] == player) hasMe = true;
                        else if (currentBoard[cx][cy] == opponent) hasOp = true;

                        // 扩散到周围
                        for (int k = 0; k < 8; ++k)
                        {
                            int nx = cx + dirs[k][0];
                            int ny = cy + dirs[k][1];

                            // 边界检查 && 不是障碍物 && 未访问
                            if (nx >= 0 && nx < N && ny >= 0 && ny < N && 
                                currentBoard[nx][ny] != -1 && !visited[nx][ny])
                            {
                                visited[nx][ny] = true;
                                q.push({nx, ny});
                            }
                        }
                    }

                    // --- 区域遍历结束，判断归属 ---
                    if (hasMe && !hasOp) 
                    {
                        // 只有我在里面：这是我的私有领地
                        mySecureTerritory += emptyCount;
                    }
                    else if (!hasMe && hasOp) 
                    {
                        // 只有对手在里面：这是他的私有领地
                        opSecureTerritory += emptyCount;
                    }
                    // 如果 hasMe && hasOp，说明是公共交战区，不做额外处理，留给之前的 BFS 去抢。
                }
            }

            // 确定性领地的价值非常高，因为不需要争抢
            // 我们给每个确定性格子 20 分的权重（比普通 BFS 的距离分高得多）
            return (mySecureTerritory - opSecureTerritory) * 20; 
        }
        int evaluation(int currentBoard[N][N], int player)
        {
            // --- 0. 计算游戏进度 (Game Stage) ---
            int arrowCount = 0;
            for(int i=0; i<N; ++i)
                for(int j=0; j<N; ++j)
                    if(currentBoard[i][j] == -1) arrowCount++;

            // 棋盘一共100格，减去8个皇后的位置，最多能射92支箭。
            // 我们定义：
            // 0-30 支箭：开局阶段 (Early)
            // 30-70 支箭：中局阶段 (Mid)
            // 70+ 支箭： 终局阶段 (Late)
            
            // 动态权重算法：
            // 灵活性权重 (wMob): 开局极高(20)，最后降低(2)
            // 领地权重 (wTerr): 开局很低(1)，最后升高(15)
            
            // 随着 arrowCount 变大，wMob 变小，wTerr 变大
            int wMob = 20 - (arrowCount * 18 / 92); 
            if (wMob < 2) wMob = 2; // 保底权重

            int wTerr = 2 + (arrowCount * 13 / 92);
            if (wTerr > 15) wTerr = 15; // 封顶权重

            int scoreTerritory = 0;
            int opponent = 3 - player;
            const int INF = 0x3f3f3f3f;

            queue<pair<int, int>> qp;
            queue<pair<int, int>> qo;
            
            static int distancep[N][N];
            static int distanceo[N][N];
            
            memset(distancep, 0x3f, sizeof(distancep));
            memset(distanceo, 0x3f, sizeof(distanceo));

            // 1. 寻找所有棋子并初始化 BFS 起点
            for(int i = 0; i < N; i++)
            {
                for(int j = 0; j < N; j++)
                {
                    if(currentBoard[i][j] == player)
                    {
                        qp.push({i,j});
                        distancep[i][j] = 0;
                    }
                    else if(currentBoard[i][j] == opponent)
                    {
                        qo.push({i,j});
                        distanceo[i][j] = 0;
                    }
                }
            }

            int dirs[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};

            // 2. 己方 BFS (Queen Distance)
            while(!qp.empty())
            {
                auto [x,y] = qp.front(); 
                qp.pop();
                
                for(int d = 0; d < 8; d++)
                {
                    int nx = x + dirs[d][0];
                    int ny = y + dirs[d][1];
                    
                    while(nx >= 0 && nx < N && ny >= 0 && ny < N && currentBoard[nx][ny] == 0)
                    {
                        if(distancep[nx][ny] == INF)
                        {
                            distancep[nx][ny] = distancep[x][y] + 1;
                            qp.push({nx,ny});
                        }
                        
                        nx += dirs[d][0];
                        ny += dirs[d][1];
                    }
                }
            }

            // 3. 对手 BFS
            while(!qo.empty())
            {
                auto [x,y] = qo.front(); 
                qo.pop();
                
                for(int d = 0; d < 8; d++)
                {
                    int nx = x + dirs[d][0];
                    int ny = y + dirs[d][1];
                    
                    while(nx >= 0 && nx < N && ny >= 0 && ny < N && currentBoard[nx][ny] == 0)
                    {
                        if(distanceo[nx][ny] == INF)
                        {
                            distanceo[nx][ny] = distanceo[x][y] + 1;
                            qo.push({nx,ny});
                        }
                        
                        nx += dirs[d][0];
                        ny += dirs[d][1];
                    }
                }
            }

            for(int i = 0; i < N; i++)
            {
                for(int j = 0; j < N; j++)
                {
                    if(currentBoard[i][j] != 0) continue; 

                    if(distancep[i][j] == INF && distanceo[i][j] == INF) continue;

                    if(distancep[i][j] < distanceo[i][j])
                        scoreTerritory++; 
                    else if(distancep[i][j] > distanceo[i][j])
                        scoreTerritory--; 
                    
                }
            }
            
            int myMobility = calculateMobility(currentBoard, player);
            int opMobility = calculateMobility(currentBoard, opponent);
            int scoreMobility = myMobility - opMobility;

            int scoreRoom = calculateRoomScore(currentBoard, player);

            return (scoreTerritory * wTerr) + (scoreMobility * wMob) + scoreRoom;
        }
        vector<Move> generateAllMoves(int currentBoard[N][N], int player)
        {
            vector<Move> moves;
            for (int x1 = 0; x1 < N; ++x1)
            {
                for (int y1 = 0; y1 < N; ++y1)
                {
                    if (currentBoard[x1][y1] == player)
                    {
                        for (int dx = -1; dx <= 1; ++dx)
                        {
                            for (int dy = -1; dy <= 1; ++dy)
                            {
                                if (dx == 0 && dy == 0) continue;
                                int nx = x1 + dx;
                                int ny = y1 + dy;
                                while (nx >= 0 && nx < N && ny >= 0 && ny < N && currentBoard[nx][ny] == 0)
                                {
                                    for (int adx = -1; adx <= 1; ++adx)
                                    {
                                        for (int ady = -1; ady <= 1; ++ady)
                                        {
                                            if (adx == 0 && ady == 0) continue;
                                            int ax = nx + adx;
                                            int ay = ny + ady;
                                            int currentcountent=currentBoard[ax][ay];
                                            if(ax==x1 && ay==y1) currentcountent=0; // 发射点是皇后原位置
                                            while (ax >= 0 && ax < N && ay >= 0 && ay < N && currentcountent == 0)
                                            {
                                                moves.push_back(make_tuple(x1, y1, nx, ny, ax, ay));
                                                ax += adx;
                                                ay += ady;
                                                if(ax>=0 && ax<N && ay>=0 && ay<N)
                                                    currentcountent=currentBoard[ax][ay];
                                                if(ax==x1 && ay==y1) currentcountent=0; // 发射点是皇后原位置
                                            }
                                        }
                                    }
                                    nx += dx;
                                    ny += dy;
                                }
                            }
                        }
                    }
                }
            }
            return moves;
        }
        int getMoveScore(const Move& move, int currentBoard[N][N], int opponent) 
        {
            auto [x1, y1, x2, y2, ax, ay] = move;
            
            int minDistance = 100; // 随便一个大数
            
            // 寻找所有对手皇后的位置
            for(int r = 0; r < N; r++) {
                for(int c = 0; c < N; c++) {
                    if(currentBoard[r][c] == opponent) {
                        // 计算切比雪夫距离 (Chebyshev Distance): max(|dx|, |dy|)
                        // 因为皇后是走米字的，切比雪夫距离更能代表“几步能走到”
                        int dist = max(abs(ax - r), abs(ay - c));
                        if(dist < minDistance) minDistance = dist;
                    }
                }
            }
    
            // 距离越小越好，所以返回负的距离（或者用 10 - distance）
            return -minDistance;
        }

        void sortMoves(vector<Move>& moves, int currentBoard[N][N], int player) {
            int opponent = 3 - player;
            
            // 使用 std::sort 和 lambda 表达式进行排序
            // 我们希望分数高（距离对手近）的排在前面
            sort(moves.begin(), moves.end(), [&](const Move& a, const Move& b) {
                return getMoveScore(a, currentBoard, opponent) > getMoveScore(b, currentBoard, opponent);
            });
        }
        void applyMove(int currentBoard[N][N], const Move &move)
        {
            int x1, y1, x2, y2, ax, ay;
            tie(x1, y1, x2, y2, ax, ay) = move;
            currentBoard[x2][y2] = currentBoard[x1][y1];
            currentBoard[x1][y1] = 0;
            currentBoard[ax][ay] = -1; // 射箭
        }
        int alphabeta(int currentboard[N][N],int depth,int alpha,int beta,int player,clock_t startT)
        {
            static int nodesCheck=0;
            if(++nodesCheck % 2048 == 0) 
            {
                if((double)(clock() - startT) / CLOCKS_PER_SEC > 10) throw 1; // 抛出异常中断
            }
            if (depth == 0)
            {
                return evaluation(currentboard, player);
            }
            vector<Move> moves = generateAllMoves(currentboard, player);
            if (moves.empty())
            {
                return -10000+depth;
            }
            sortMoves(moves, currentboard, player);
            // 最大化玩家
            int bestValue=-1e9;
            for (const Move &move : moves)
            {
                int newBoard[N][N];
                memcpy(newBoard, currentboard, sizeof(newBoard));
                applyMove(newBoard, move);
                int value = -alphabeta(newBoard, depth - 1, -beta, -alpha, 3 - player, startT);
                if (value > bestValue)
                {
                    bestValue = value;
                }
                alpha = max(alpha, value);
                if (alpha >= beta)
                {
                    break; // Beta 剪枝
                }
            }
            return bestValue;
        }
        // ==========================================
        // 功能块：迭代加深驱动 (Iterative Deepening Driver)
        // 逻辑：从深度 1 开始逐层搜索，直到时间耗尽，保留最深层的完整结果
        // ==========================================
        void solve() 
        {
            clock_t startT = clock();
            
            // 1. 先生成所有移动
            vector<Move> moves = generateAllMoves(board, currentPlayer);
            if (moves.empty()) {
                cout << "AI has no moves! AI Lost." << endl;
                return; 
            }

            // 初始化 bestMove 为第一个合法移动作为保底
            // 这样即使 10秒内连深度1都没搜完，AI 也会随便走一步合法的，而不是报错或不动
            sortMoves(moves, board, currentPlayer);
            Move bestMove = moves[0]; 

            int maxDepthReached = 0;
            try {
                for (int depth = 1; depth <= 20; depth++) {
                    
                    int alpha = -1e9, beta = 1e9;
                    int bestVal = -1e9;
                    
                    // 用于记录“当前这一层深度”找到的最佳移动
                    Move currentDepthBest = moves[0]; 
                    
                    for (const auto& m : moves) {
                        int temp[N][N];
                        memcpy(temp, board, sizeof(temp));
                        applyMove(temp, m);

                        int val = -alphabeta(temp, depth - 1, -beta, -alpha, 3 - currentPlayer, startT);

                        if (val > bestVal) {
                            bestVal = val;
                            currentDepthBest = m;
                        }
                        alpha = max(alpha, val);
                        
                        if((double)(clock() - startT) / CLOCKS_PER_SEC > 4.5) throw 1;
                    }

                    // 如果这一层完整跑完没超时，才更新全局 bestMove
                    // 去掉了前面的 "Move" 声明符，确保更新的是外部变量
                    bestMove = currentDepthBest; 
                    maxDepthReached = depth;
                    
                    if(bestVal > 5000) break; 
                }
            } 
            catch (int) {
                // 超时直接捕获，bestMove 保留的是上一个完整深度的结果
            }

            // 执行决策
            auto [x1, y1, x2, y2, ax, ay] = bestMove;
            
            // 调试输出（可选）：查看AI最终决定
            // cout << "AI Move: " << x1 << "," << y1 << " -> " << x2 << "," << y2 << " shoot " << ax << "," << ay << endl;

            makeMove(x1, y1, x2, y2);
            shootArrow(ax, ay);
            switchPlayer();
            displayBoard();
        }
        bool showInGameMenu(Amazons &game) 
        {
            while(true) 
            {
            cout << "\n[Game Menu]" << endl;
            cout << "1. Continue Game" << endl;
            cout << "2. Save Game" << endl;
            cout << "3. Load Game" << endl;
            cout << "4. Quit to Main Menu" << endl;
            cout << "Choice: ";
            
            int choice;
            cin >> choice;

            if (choice == 1) return false; // 继续
            if (choice == 2) 
            {
                string name;
                cout << "Enter filename to save (e.g. save.txt): ";
                cin >> name;
                if(game.saveGame(name)) cout << "Saved successfully!\n";
                else cout << "Save failed!\n";
            }
            else if (choice == 3) 
            {
                string name;
                cout << "Enter filename to load: ";
                cin >> name;
                if(game.loadGame(name)) 
                {
                    cout << "Loaded successfully!\n";
                    game.displayBoard(); // 刷新显示
                    return false; // 继续玩
                }
                else cout << "Load failed!\n";
            }
            else if (choice == 4) 
            {
                return true; // 退出
            }
        }
}
};
int main()
{
    Amazons game;
    int choice;
    while (true) {
        system("cls");
        cout << "=== AMAZONS GAME ===" << endl;
        cout << "1. New Game" << endl;
        cout << "2. Load Game" << endl;
        cout << "3. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (choice == 3) break; // 退出程序

        if (choice == 2) {
            string name;
            cout << "Enter filename: ";
            cin >> name;
            if (!game.loadGame(name)) {
                cout << "File not found! Press enter to continue...";
                cin.ignore(); cin.get();
                continue;
            }
        } 
        else {
            // 新游戏
            game.initializeBoard();
            cout << "Choose your player (1=First/Black, 2=Second/White): ";
            int tmp;
            cin >> tmp;
            game.decidehumanplayer(tmp);
        }

        // --- 游戏循环 ---
        game.displayBoard();
        bool gameRunning = true;
        
        while (gameRunning && game.hasValidMoves(game.getCurrentPlayer()))
        {
            int current = game.getCurrentPlayer();

            if (current == game.gethumanplayer())
            {
                // 人类回合
                int x1, y1, x2, y2, ax, ay;

                cout << "Enter move 'x1 y1 x2 y2' (or -1 to Menu): ";
                cin >> x1; 
                
                // 【核心逻辑】检测特殊输入
                if (x1 == -1) {
                    if (game.showInGameMenu(game)) {
                        gameRunning = false; // 退出到主菜单
                        break;
                    }
                    game.displayBoard(); // 从菜单回来后重画棋盘
                    continue; // 重新开始本回合循环
                }
                
                // 如果不是菜单，继续读取剩下3个坐标
                cin >> y1 >> x2 >> y2;

                if (!game.isValidMove(x1, y1, x2, y2))
                {
                    cout << "Invalid move! Path blocked or rule violation." << endl;
                    cout << "Press Enter to try again...";
                    cin.ignore(); cin.get(); // 暂停一下让玩家看到错误
                    game.displayBoard();
                    continue;
                }

                game.makeMove(x1, y1, x2, y2);
                game.displayBoard();

                // 射箭阶段
                while (true) {
                    cout << "Enter arrow shot 'ax ay': ";
                    cin >> ax >> ay;
                    // 注意：射箭也是一次“移动”，起飞点是棋子落点 (x2, y2)
                    if (game.isValidMove(x2, y2, ax, ay)) {
                        game.shootArrow(ax, ay);
                        break;
                    }
                    cout << "Invalid arrow shot! Try again." << endl;
                }
                
                game.displayBoard();
                game.switchPlayer();
            }
            else
            {
                // AI 回合
                game.solve(); 
            }
        }

        if (gameRunning) {
            cout << "Game Over! Winner: " << (3 - game.getCurrentPlayer()) << endl;
            system("pause");
        }
    }
    
    return 0;
}