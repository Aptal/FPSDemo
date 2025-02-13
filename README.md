# FPSDemo
2024腾讯游戏客户端公开课相关  
基于UE5.4的游戏First Person模板开发

# 目录
- [课堂笔记](#课堂笔记)
- [作业完成情况](#作业完成情况)
- [完成情况说明](#完成情况说明)
- [截图展示](#截图展示)

# 课堂笔记
## 第一周
[《UE入门》](https://www.mubu.com/doc/2oJdnkSXkXl)

## 第二周
[《游戏模式》](https://www.mubu.com/doc/2pDGzonBRkl)

## 第三周
[《UE5的C++代码规范》](https://www.mubu.com/doc/1smLSvCujOB)

## 第四周
[《UMG界面》](https://www.mubu.com/doc/1I4ao6djV2B)

## 第五周
[《UE5的骨骼动画》](https://www.mubu.com/doc/AejDxU9ZfB)

## 第六周
《游戏物理》-推迟

## 第七章
《渲染基础》

## 第八周
[《AI技术介绍》](https://www.mubu.com/doc/CitINrN8h5)

## 第九周
[《UE网络同步》](https://www.mubu.com/doc/2fmoMnj_gh5)

## 第十周
[《FP5游戏开发基础》](https://www.mubu.com/doc/6KbxBUSRxx5)

## 第十一周
[《游戏物理》](https://www.mubu.com/doc/4mk3chNqAx5)

# 作业完成情况
## 第一周
- [x] 源码编译UE5，创建C++工程（First Person模板）  
- [x] 编译构建安装包，可以在安卓机运行（画质好差~未上传apk ~~github lfs 容量超载了~~）

## 第二周
### 物件规则：
- [x] 1. 射击命中方块，获得积分X (Score) 分
- [x] 2. 子弹命中方块后销毁
- [x] 3. 方块被子弹命中后，缩放为Y (HitScale) 倍，再次被命中后销毁  
[查看积分、缩放设置面板](#CubeInfo)  

### 游戏流程：
- [x] 1. 游戏开始时随机N (ImportantGoalCount) 个方块成为“重要目标”，射击命中后获得双倍积分
- [x] 2. 游戏开始后限时T (Seconds) 秒，时间到后游戏结算，打印日志输出每个玩家获得的积分和所有玩家获得的总积分  
[查看时间，重要目标设置面板](#GameInfo)  
[击中大小对比](#HitShowImg)

### 附加题
- [x] 1. 利用UMG制作结算UI替代日志打印  
[结算面板展示](#ScorePanelImg)
- [-] 2. 支持多人联机


## 第四周
- [x] 1.实现登录界面（需要输入用户名和密码，其中密码加密显示，有确认按钮）  
[登陆页面展示](#LoginImg)
- [x] 2.实现加载界面（要有动画表传达正在加载）  
[加载页面展示](#LoadingImg)
- [x] 3.实现射击游戏操作面板（要有血条，子弹数，击中玩家会发生变化的准星  
[操作面板展示](#UIImg)

## 第五周
- [x] 1.实现敌人的基础移动动画蓝图，并尽可能优化表现。  
[动画蓝图设置与展示](#动画蓝图设置与展示)
- [x] 2.实现敌人的死亡动画，并尽可能优化表现（如添加多方向死亡动画等）。  
[敌人死亡动画展示](#敌人死亡动画展示)
- [ ] 3.实现近战击败敌人的功能和动画表现。（选做）

## 第六周
- [ ] 1. 增加阴影
- [ ] 2. Renderdoc分析游戏
- [ ] 3. 增加一个渲染feature（如描边等）或者优化当前的渲染功能（选做）

## 第七章
- [x] 1.实现NPC AI按照指定路线巡逻。
- [x] 2.实现NPC寻路过程中，累了主动去几个随机位置休息
- [x] 3.实现NPC遇到玩家以后主动和玩家进行打招呼。

## 第八周
- [x] 1. 开启CS网络同步模式，开启角色和投掷物移动同步
- [x] 2. 实现客户端发起开火，服务器创建投掷物并广播。
- [x] 3. 服务器实现投掷物命中伤害逻辑，并广播命中事件和角色血量变化

## 第十周
### 鱼群效果 Flocking
- [ ] 1. 一个鱼群有一个虚拟领袖，决定航向
- [ ] 2. 同一鱼群，鱼和鱼之间的间距要保持在一定范围内，鱼群和鱼群之间亦然
- [ ] 3. 最多8群鱼，一群鱼最多32条鱼
- [ ] 4. 尽可能让表现自然，尽可能地优化性能，给出程序不同阶段的性能数据
- [ ] 5. 2D / 3D均可，不限引擎，框架，语言
- [ ] 6. 如果时间所限不能完成所有特性，可以在文档中写出优化思路

# 完成情况说明

## 截图展示
### 作业2
#### 积分、缩放设置面板
<a name="CubeInfo"></a>
![积分、缩放设置面板](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/2Homework/2-1.png?raw=true "积分、缩放设置面板")

#### 时间，重要目标设置面板
<a name="GameInfo"></a>
![时间，重要目标设置面板](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/2Homework/2-2.png?raw=true "时间，重要目标设置面板")

#### 击中大小、重要目标对比
“重要目标”被标记为黄金色，击中一次缩小一倍，两次消失
<a name="HitShowImg"></a>
![击中大小对比](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/2Homework/2-3.png?raw=true)

### 作业4
#### 结算面板（每个玩家分数，总分数）
<a name="ScorePanelImg"></a>
![结算面板](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/2Homework/2-4.png?raw=true)

#### 登陆页面
<a name="LoginImg"></a>
![登陆页面](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/4Homework/4-1.png?raw=true)

#### 加载页面
登陆页面点击登录后，加载界面（强制delay 3s）右下角使用ue自带的转圈，中间的字体添加抖动动画，3s后自动进入游戏界面
<a name="LoadingImg"></a>
![加载页面](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/4Homework/4-2.png?raw=true)

#### 操作面板
持枪时初始10个子弹，击中玩家后准星会从黑色变红色
<a name="UIImg"></a>
![操作面板](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/4Homework/4-3.png?raw=true)

### 作业5
#### 动画蓝图设置与展示
调用攻击蒙太奇中的CallDamage通知
<a name="UIImg"></a>
![动画蓝图事件图表](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/5Homework/5-1.png?raw=true)  

敌人AI行为树设置：未死亡且无寻找目标时，随机位置移动，有攻击目标后（玩家射击命中 与 感知组件观察到玩家 会设置攻击目标）跑向玩家
<a name="UIImg"></a>
![敌人AI行为树](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/5Homework/5-1-1.png?raw=true)

随机位置移动展示（速度为200，行走动画）
<a name="UIImg"></a>
![动画蓝图事件图表](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/5Homework/5-1-2.png?raw=true)

追击玩家移动展示（速度为400，跑步动画）
<a name="UIImg"></a>
![动画蓝图事件图表](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/5Homework/5-1-3.png?raw=true)

攻击玩家动画展示（到达攻击目标范围内，攻击动画）
<a name="UIImg"></a>
![动画蓝图事件图表](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/5Homework/5-1-4.png?raw=true)


#### 敌人死亡动画展示
敌人AI死亡动画展示（被玩家命中5次(敌人AI血量100，子弹伤害50)，死亡动画）  
在服务器端的玩家左下角的血条是被敌人攻击后的（暂定血量200，敌人攻击伤害值50）  
敌人AI被击杀后，血条UI销毁
<a name="UIImg"></a>
![死亡动画1](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/5Homework/5-2.png?raw=true)
![死亡动画2](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/5Homework/5-2-1.png?raw=true)

### 作业7
#### 路线巡航设置与展示
路线使用spline设置如图  
<a name="UIImg"></a>
![7](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/5Homework/7-1-1.png?raw=true)  

NPC巡航时会增加疲惫值（Fatigue），达到阈值随机找路线内某点休息，然后重置疲惫值
<a name="UIImg"></a>
![7](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/5Homework/7-1-2.png?raw=true)

巡航移动动画展示
<a name="UIImg"></a>
![7](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/5Homework/7-1-3.png?raw=true)

#### NPC休息展示

休息动画展示
<a name="UIImg"></a>
![7](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/5Homework/7-2.png?raw=true)

#### NPC与玩家交互

通过PawnSensing判断前方是否有玩家，展示UI并给玩家补充子弹  
<a name="UIImg"></a>
![7](https://github.com/Aptal/FPSDemo/blob/main/HomeworkScreenshot/5Homework/7-3-1.png?raw=true)



#### todo  
- [x] 补充弹药npc的寻路、休息、打招呼
- [ ] 多人视角下完整的玩家骨骼
- [ ] 联网登陆

### 02.11
- 添加敌人攻击时的攻击范围判定
- 添加打到玩家后，玩家血屏效果

### 02.09
- 添加敌人AI，当视野范围内有玩家或者被玩家射到会追踪玩家，距离玩家一定距离内触发攻击动画
- 玩家射击敌人会造成20点伤害，敌人总共100点血量
- [x] todo：敌人血条，敌人攻击玩家伤害值

### 02.06
 - 开火动画同步，倒计时正确同步，射击者（子弹拥有者）完善
 - [x] todo：子弹余量UI同步，得分显示，结算面板(显示bug)

### 02.05
- 将Fire时的Projectile生成从Weapon_Component中移到Character，终于是能正确同步在服务端跟客户端了，还需要完善数量变化的同步

### 12.16
- 射击者的获取有点问题

### 12.15
- 新建gameinstance会出现访问不到map（索引为空，打开level失败）的情况，暂时采用从ButtonClick中 清空widget->打开loading widget-> delay 3s->打开新level


### 12.04
- 第二周目标基本完成：作业中的游戏相关属性括号内的名称均在蓝图中暴露
- 差多人网络同步：未开始
- UMG结算UI：类似当前HUD的形式，框架基本完成