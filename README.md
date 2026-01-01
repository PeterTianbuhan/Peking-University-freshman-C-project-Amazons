# Peking-University-freshman-C-project-Amazons
相较于初始版本，当前版本（v2.0）进行了核心算法重构与策略升级，主要包含以下改进：
1. 核心 Bug 修复 (Critical Fix)
变量遮蔽修复 (Variable Shadowing Fix): 修复了 solve() 函数中局部变量遮蔽外部变量导致 Bot 输出 0 0 0 0 0 0 非法移动的问题。现在 Bot 能正确回传迭代加深搜索到的最佳着法。
2. 估值函数升级 (Evaluation Function Upgrade)
从单一的“距离评估”升级为多维混合评估体系：
灵活性加权 (Mobility Heuristic): 引入了对当前棋子可选步数的计算。Bot 现在会主动避免被封锁，并在开局阶段极力抢占高机动性位置。
区域分析 (Room Analysis / Component Detection): 实现了基于 Flood Fill (泛洪算法) 的连通区域检测。
能够识别“封闭领地（Secure Territory）”。
对于完全属于我方的封闭区域给予极高权重（+20分/格），引导 Bot 进行“关门打狗”式的封锁策略。
3. 动态策略系统 (Adaptive Strategy System)
自适应权重 (Adaptive Weights): 摒弃了静态参数，实现了基于游戏进度的动态权重调整。
开局 (Early Game): 极高权重赋予灵活性 (Mobility)，抢占中心。
终局 (Endgame): 权重平滑过渡至领地 (Territory)，专注填满格子。
使用线性插值算法根据棋盘上箭矢的数量（arrowCount）动态计算权重。
4. 搜索效率优化 (Search Efficiency)
着法排序 (Move Ordering): 在 Alpha-Beta 剪枝前对生成的着法进行预排序。
优先搜索“攻击性着法”（即箭矢落在对手皇后附近的着法，计算切比雪夫距离）。
显著提高了剪枝效率，使得在同样时间内能搜索更深层数。