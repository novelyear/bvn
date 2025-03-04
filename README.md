# 仿《死神vs火影》

视频演示链接： https://www.bilibili.com/video/BV16gCaYBE8u/?share_source=copy_web&vd_source=e7385d4618ca5d19b02c5fd56d72182c

# 目录

[一、 游戏概述 3](#_Toc185173544)

[1.1 游戏简介 3](#_Toc185173545)

[1.2 游戏开发环境 4](#_Toc185173546)

[1.3 总体工作量 4](#_Toc185173547)

[二、 游戏内容 5](#_Toc185173548)

[2.1 游戏规则 5](#_Toc185173549)

[2.2 游戏操作方式 5](#_Toc185173550)

[2.3 游戏开始界面 6](#_Toc185173551)

[2.4 游戏选择地图界面 6](#_Toc185173552)

[2.5 游戏选择人物界面 7](#_Toc185173553)

[2.6 游戏战斗界面 7](#_Toc185173554)

[三、 游戏元素 8](#_Toc185173555)

[3.1 人物 8](#_Toc185173556)

[3.1.1 我爱罗（Gaara） 8](#_Toc185173557)

[3.1.2 仙鸣（NarutoS） 8](#_Toc185173558)

[3.2 战斗特效 9](#_Toc185173559)

[3.3 行为特效 9](#_Toc185173560)

[3.4 地图 10](#_Toc185173561)

[3.4.1 地图1：月夜楼顶 10](#_Toc185173562)

[3.4.2 地图2：终末之谷 10](#_Toc185173563)

[3.5 血量条、Chakra条、气条 11](#_Toc185173564)

[四、 核心逻辑 12](#_Toc185173565)

[4.1 总体逻辑设计 12](#_Toc185173566)

[4.1.1 开始界面逻辑 12](#_Toc185173567)

[4.1.2 选地图界面逻辑 12](#_Toc185173568)

[4.1.3 选人界面逻辑 12](#_Toc185173569)

[4.1.4 战斗逻辑 12](#_Toc185173570)

[4.2 代码架构设计 13](#_Toc185173571)

[4.2.1 整体架构简述 13](#_Toc185173572)

[五、 游戏难点、亮点及实现方案 15](#_Toc185173573)

[5.1 素材收集、整理 15](#_Toc185173574)

[5.1.1 素材收集 15](#_Toc185173575)

[5.1.2 素材整理 15](#_Toc185173576)

[5.2 人物动画 17](#_Toc185173577)

[5.3 特效动画 18](#_Toc185173578)

[5.3.2 特效池 18](#_Toc185173579)

[5.3.3 战斗特效 19](#_Toc185173580)

[5.3.4 通用特效 19](#_Toc185173581)

[5.4 状态转移 19](#_Toc185173582)

[5.5 碰撞检测 20](#_Toc185173583)

[5.5.1 人物与人物碰撞 20](#_Toc185173584)

[5.5.2 人物与特效碰撞 21](#_Toc185173585)

[5.5.3 人物与地图碰撞 22](#_Toc185173586)

[5.6 镜头跟随 24](#_Toc185173587)

[5.6.2 不跟随镜头元件 25](#_Toc185173588)

[5.6.3 跟随镜头元件 25](#_Toc185173589)

[5.7 打击感 25](#_Toc185173590)

[5.7.1 震屏 25](#_Toc185173591)

[5.7.2 顿帧 26](#_Toc185173592)

[5.7.3 打击感音效 26](#_Toc185173593)

[5.8 键位设置 27](#_Toc185173594)

[5.8.1 长按、短按 27](#_Toc185173595)

[5.8.2 组合键 28](#_Toc185173596)

[5.9 战斗效果 28](#_Toc185173597)

[5.9.1 前摇、后摇 28](#_Toc185173598)

[5.9.2 大招时停动画 29](#_Toc185173599)

[5.9.3 受击硬直、击飞 30](#_Toc185173600)

[5.10 性能优化 30](#_Toc185173601)

[5.10.1 限制帧率 30](#_Toc185173602)

[5.10.2 纹理图集 30](#_Toc185173603)

[六、 心得体会 31](#_Toc185173604)

[6.1 游戏开发历程 31](#_Toc185173605)

[6.2 游戏版本迭代 31](#_Toc185173606)

[6.3 结语 31](#_Toc185173607)

# 游戏概述

## 游戏简介

本游戏参照4399上的经典2D Flash 横板格斗游戏《死神vs火影》（Bleach vs Naruto）开发。

游戏实现了《死神vs火影》的大部分基本效果，玩家通过9个键控制角色，能够使用：

| 三段普攻（仙鸣为四段） | S远攻二段（仅仙鸣） |
| ---------------------- | ------------------- |
| W普攻                  | W远攻二段（仅仙鸣） |
| S普攻                  | 空中远攻            |
| 空中普攻               | 大招                |
| 远攻                   | W大招               |
| S远攻                  | S大招               |
| W远攻                  | 空中大招（仅仙鸣）  |

招式汇总表

共14种攻击方式进行战斗，能够左右移动、二段跳跃、冲刺、防御，具备双人格斗游戏的基本玩法。

本游戏提供了较好的打击感和动画表现，招式繁多，且作为双人游戏，可玩性较高，玩家通过对角色的理解合理搭配连招，能够获得较好的游戏体验。

## 游戏开发环境

系统：windows 11

环境：C++ 17，visual studio community 2019

C++图形库：SFML 2.6.2

## 总体工作量

![代码量展示](https://s3.bmp.ovh/imgs/2024/12/20/cd3c50d3c815a0d4.png)

最终项目总行数为：4887行，有效代码行数为：4171行。

素材使用情况：

| 素材类型             | 数量（张） |
| -------------------- | ---------- |
| 人物头像             | 2          |
| 地图                 | 6          |
| 我爱罗人物动画帧     | 1251       |
| 我爱罗技能特效动画帧 | 312        |
| 仙鸣人物动画帧       | 1286       |
| 仙鸣技能特效动画帧   | 47         |
| 开始界面UI           | 93         |
| 战斗UI               | 17         |
| 通用特效动画帧       | 61         |
| 音效                 | 23（个）   |

素材类型汇总表

总计3075张图片，23个MP3文件。

# 游戏内容

## 游戏规则

进入游戏后，鼠标右键点击屏幕任意位置唤出开始游戏按钮，右键点击开始游戏按钮后进入地图选择界面，选择地图后进入人物选择界面，双方选择完人物后，待游戏加载完成后进入战斗。

两位玩家操控两个角色在选定的地图中战斗，战斗期间击中敌方或被击中都会积攒“气”，气共有3段，积攒满一段后即可消耗一段气释放大招或W大招，气满三段之后可消耗全部气释放超级大招——S大招。按下S键可防御敌方攻击——大幅减少伤害并免疫硬直和击飞效果，但每次受击会消耗Chakra，Chakra消耗光后无法再防御。冲刺也会消耗Chakra，当不处于冲刺状态和防御状态时，Chakra会自动恢复。

当一方受到最后一击，生命值清零时，决出胜负。

## 游戏操作方式

游戏分为1P和2P，键位设置如下：

| 操作类型      | 1P键位 | 2P键位               |
| ------------- | ------ | -------------------- |
| 向左移动      | A      | 方向左键             |
| 向右移动      | D      | 方向右键             |
| 跳跃          | K      | 小键盘数字2          |
| 冲刺          | L      | 小键盘数字3          |
| 防御          | S      | 方向下键             |
| 主动落下平台  | S+K    | 方向下键+小键盘数字2 |
| 普攻          | J      | 小键盘数字1          |
| S普攻         | S+J    | 方向下键+小键盘数字1 |
| W普攻         | W+J    | 方向上键+小键盘数字1 |
| 远攻/空中远攻 | U      | 小键盘数字4          |
| W远攻         | W+U    | 方向上键+小键盘数字4 |
| S远攻         | S+U    | 方向下键+小键盘数字4 |
| 大招/空中大招 | I      | 小键盘数字5          |
| W大招         | W+I    | 方向上键+小键盘数字5 |
| S大招         | S+I    | 方向下键+小键盘数字5 |

玩家键位表

## 游戏开始界面

界面1：具有动效以及主题音乐，详见演示视频

![开始界面首页](https://s3.bmp.ovh/imgs/2024/12/20/c75921dc53a9a159.png)

鼠标单击任何位置进入界面2：

界面中间出现按钮，鼠标悬停后按钮样式变化

## 游戏选择地图界面

通过左右键选择地图

![选择地图界面](https://s3.bmp.ovh/imgs/2024/12/20/14bae6dbd685846e.png)

## 游戏选择人物界面

通过左右键先选择1P的角色，再选择2P的角色，选择结束后进入战斗界面。

![选择人物界面](https://s3.bmp.ovh/imgs/2024/12/20/dc90a44d8a94ed24.png)

## 游戏战斗界面

![战斗界面组图](https://s3.bmp.ovh/imgs/2024/12/20/d0f816e696679ec2.png)

# 游戏元素

## 人物

### 我爱罗（Gaara）

![我爱罗素材部分展示图](https://s3.bmp.ovh/imgs/2024/12/20/a73b25c007a9e9dd.png)

### 仙鸣（NarutoS）

![仙鸣素材部分展示图](https://s3.bmp.ovh/imgs/2024/12/20/0be952abcb07c9f5.png)

## 战斗特效

仙鸣的部分战斗特效动画帧：

![螺旋手里剑特效](https://s3.bmp.ovh/imgs/2024/12/20/468ba27eb21a5475.png)

我爱罗的部分战斗特效动画帧：

![我爱罗的部分战斗特效](https://s3.bmp.ovh/imgs/2024/12/20/ac4bd72698edf214.png)

## 行为特效

包含地面冲刺尾尘、空中冲刺尾烟、大招闪光特效、落地灰尘

## 地图

### 地图1：月夜楼顶

分为地图背景和地图前景，其中前景具有多个平台，可供人物站立。

背景始终填满视图图层底部，而前景固定不动，形成固定的2D世界参考系系。

![月夜楼顶地图](https://s3.bmp.ovh/imgs/2024/12/20/6a6283626c5e13b1.png)

### 地图2：终末之谷

分为前景和背景，其中前景具有多个平台可供站立

![终末之谷地图](https://www.helloimg.com/i/2024/12/20/676527c706674.png)

## 血量条、Chakra条、气条

每个人物都具有自己的战斗相关UI，包括：血条框blood\_bar、血条blood、Chakra框、Chakra条（表示充足的蓝色条、表示不足的粉色条）、Chakra示意文字贴图、气条框、气段数字、不同段对应的气条。

# 核心逻辑

## 总体逻辑设计

### 开始界面逻辑

main函数首先执行键位映射，然后新建Game对象，运行run方法，Game对象初始状态为Init，对应开始界面，先轮播首页动画帧，轮播背景音乐。

鼠标点击后切换另一批动画帧，表现为画面从中间分开，露出内部的开始游戏按钮。

### 选地图界面逻辑

点击开始游戏按钮后Game的状态变为SelectMap，黑色为背景，绘制准备好的地图示意图片，图片周围有高光表示选择框，上有文字操作提示。选择地图后，Game类内部的Map对象获取到具体的子类对象指针，调用相应的加载方法加载地图资源。

### 选人界面逻辑

地图选择完毕后，Game的状态变为SelectCharacter，画面以黑色为背景，绘制准备好的人物头像，周围有黄色、蓝色高光框分别表示1P和2P的选择框。1P选择后，Game类的成员player获得具体的子类对象指针（Gaara或NarutoS），2P选择同理。

### 战斗逻辑

人物加载完毕后，Game类进入Playing状态，此时循环执行process、update、render三个方法，分别代表：交互层、业务层、渲染层：

|      | 交互层                                                       | 业务层                                                       | 渲染层                                                       |
| ---- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 逻辑 | 先后调用1P和2P的键盘交互方法handleMove；  在handleMove中，通过一系列实时键盘监听函数监听键盘输入，识别组合键和运动、攻击状态，同时屏蔽非法输入；  监听到键盘输入后，调用Character的相关方法，改变人物的状态，赋予速度等 | 首先调用pause暂停管理器的更新方法，处理两个人物的暂停消息队列；  根据暂停情况选择性调用1P和2P的update方法；  然后处理两个人物的震屏、音乐触发消息队列；  最后更新视图位置。 | 首先判断是否触发大招的部分暂停，选择渲染黑色背景或正常地图背景；  然后以：人物、特效、战斗UI的顺序绘制图像；  最后设置视图位置，将视图放在2D世界的一个位置，表示窗口。 |

游戏主循环架构

同时，循环播放战斗背景音乐。

一方生命值清零后，Game进入Over状态，屏幕中间出现结算字样，更新停止，待鼠标点击后关闭窗口结束。

## 代码架构设计

### 整体架构简述



整体类图

代码中各类的职责简述：

| 类名             | 职责简述                                                     |
| ---------------- | ------------------------------------------------------------ |
| Game             | 游戏整体流程控制                                             |
| Character        | 抽象类，包含各种基本属性和方法，作为基类供各子类继承         |
| CharacterFactory | 工厂类，以工厂模式生产具体的人物子类指针                     |
| NarutoS          | 代表仙鸣角色，继承Character，通过重写实现个性化的机制        |
| Gaara            | 代表我爱罗角色，继承Character，通过重写实现个性化机制        |
| Effect           | 抽象类，包含特效的各种基本属性和方法，作为抽象类供各子类继承 |
| EffectPool       | 特效池，包含多个Effect的指针，封装特效，对外提供产生特效的接口和绘制特效的接口 |
| DefaultEffect    | 继承Effect类，代表通用特效，包含加载、更新、绘制等方法       |
| NarutoEffect     | 继承Effect类，代表NarutoS的攻击特效                          |
| GaaraEffect      | 继承Effect类，代表Gaara的攻击特效                            |
| Map              | 抽象类，包含地图的基本属性和方法，供具体的地图子类继承       |
| MapFactory       | 工厂类，以工厂模式生产具体的地图类对象指针                   |
| Platform         | 代表地图可站立平台，用于定义平台和碰撞检测                   |
| MR               | 继承Map类，代表月夜楼顶地图(Moon night Roof)                 |
| VE               | 继承Map类，代表终末之谷地图(Valley of End)                   |
| StartUI          | 代表开始界面，负责开始界面的贴图循环播放和点击效果           |
| CameraShake      | 负责控制屏幕震动，向外提供触发屏幕震动的方法                 |
| Pause            | 负责全局暂停和部分暂停                                       |
| GameAudio        | 负责加载以及控制游戏音乐、音效的播放                         |
| CharacterState   | 枚举类，包含人物所有的状态                                   |
| EffectState      | 枚举类，包含特效的所有种类                                   |
| GameState        | 枚举类，包含游戏的5种状态                                    |
| CharacterType    | 枚举类，包含两个人物类别NarutoS和Gaara                       |
| MapType          | 枚举类，包含两个地图类别MR和VE                               |
| EventType        | 枚举类，包含事件类别，控制屏幕震动和暂停，用于事件队列机制，实现类间通信 |

类职责简述

# 游戏难点、亮点及实现方案

## 素材收集、整理

### 素材收集

最开始开发时使用github仓库：[KevinChenXue/Naruto-vs-Bleach: 2-D platform fighter game](https://github.com/KevinChenXue/Naruto-vs-Bleach)中的素材。开发到战斗阶段时发现素材严重不足，于是找到了原版游戏素材的github仓库：[5DPLAY-Game-Studio/assets\_lib: 《死神vs火影》素材库](https://github.com/5DPLAY-Game-Studio/assets_lib)

但由于《死神vs火影》使用Flash开发，素材格式为swf，无法直接查看和使用。经过搜索，使用[jindrapetrik/jpexs-decompiler: JPEXS Free Flash Decompiler](https://github.com/jindrapetrik/jpexs-decompiler)将swf文件反编译，从中选择所需的图片、声音资源并导出。

### 素材整理

问题：

1. 使用JPEX反编译导出的图片资源仍然不能直接使用，swf文件中的每个Sprite（计算机图形学概念，精灵，指具有各种属性的二维图像）导出后都是一组大小相同的图片，具有极大的空白区域（2600\*1300的图片可能只有30\*40的有效区域），需要裁切；

![直接导出的素材示例](https://www.helloimg.com/i/2024/12/20/676526b849270.png)

1. 在程序中频繁切换Sprite的纹理将会产生巨大的GPU压力，导致程序性能严重下降，所以，需要将图片合并为一张纹理图集，同时记录每张图片在纹理图集中的锚框坐标，方便Sprite单次加载纹理图片，通过切换锚框的方式切换绘制出的纹理范围；
2. 将纹理赋给Sprite后，如果直接循环播放，由于源点位置不同，会产生抖动现象，所以还需要确定所有图片的参考系源点坐标；（如下图例，直接绘制对齐的不是底部，而是顶部对齐，人物会上下抖动）

![人物抖动示意图](https://www.helloimg.com/i/2024/12/20/676526b8b7cc7.png)

1. 组图没有分区，还需要手动将每个行为对应的图组划分开

解决：

1. 使用Python编写脚本，根据找到的所有图片的共同源点坐标，自动裁切空白区域后，得到裁切后源点的相对坐标，保存在origin.txt中；

```python
import os
from PIL import Image

def crop_and_record(input_dir, output_dir, record_file):
    """
    Crop PNG images to remove blank spaces and record new center coordinates.

    Args:
        input_dir (str): Path to the folder containing input PNG images.
        output_dir (str): Path to the folder to save cropped images.
        record_file (str): Path to the file to save center coordinates.
    """
    # Ensure output directory exists
    os.makedirs(output_dir, exist_ok=True)

    # Open the record file for writing
    with open(record_file, "w") as record:
        # Iterate through sorted filenames in the input directory
        for filename in sorted(os.listdir(input_dir), key=lambda x: int(os.path.splitext(x)[0])):
            input_path = os.path.join(input_dir, filename)

            # Skip non-PNG files
            if not filename.lower().endswith(".png"):
                continue

            # Open the image
            with Image.open(input_path) as img:
                # Ensure the image is in RGBA mode
                img = img.convert("RGBA")
                bbox = img.getbbox()  # Get bounding box of non-empty regions

                if bbox is None:
                    # If the image is completely blank, skip it
                    print(f"Image {filename} is completely blank. Skipping.")
                    continue

                # Crop the image to the bounding box
                cropped_img = img.crop(bbox)

                # Calculate the new center relative to the cropped image
                original_width, original_height = img.size
                original_center = (xx, yy) # 原图的源点
                new_center = (original_center[0] - bbox[0], original_center[1] - bbox[1])

                # Save the cropped image
                output_path = os.path.join(output_dir, filename)
                cropped_img.save(output_path)

                # Write the record to the file
                record.write(f"{os.path.splitext(filename)[0]}-{new_center}\n")

                print(f"Cropped {filename}, new center: {new_center}")

if __name__ == "__main__":
    # Define input/output paths and record file
    input_directory = r""
    output_directory = r""
    record_file_path = r""

    # Run the cropping and recording function
    crop_and_record(input_directory, output_directory, record_file_path)

```

2. 使用Python编写脚本，将多张图片合并为一张大图，同时保存每张图片在大图中的锚框位置和大小，保存在anchors.txt中；

```python
from PIL import Image
import os


def pack_images_with_metadata(input_folder, origin_file, output_atlas, output_metadata):
    # 读取原点信息
    origins = {}
    with open(origin_file, "r") as f:
        for line in f:
            parts = line.strip().split("-")
            image_number = int(parts[0])  # 获取图号
            origin_coords = tuple(map(int, parts[1].strip("()").split(", ")))  # 提取 (x, y)
            origins[image_number] = origin_coords

    # 读取所有图片
    images = []
    for file_name in sorted(os.listdir(input_folder), key=lambda x: int(os.path.splitext(x)[0])):
        if file_name.endswith(".png"):
            image_number = int(os.path.splitext(file_name)[0])  # 获取图号
            image_path = os.path.join(input_folder, file_name)
            image = Image.open(image_path)
            images.append((image_number, image))

    # 排列图片并计算图集大小
    MAX_ATLAS_WIDTH = 1024
    atlas_width, atlas_height = 0, 0
    row_width, row_height = 0, 0
    packed_positions = []  # 每张图片在图集中的位置 (x, y)

    for _, img in images:
        if row_width + img.width > MAX_ATLAS_WIDTH:
            # 换行
            atlas_width = max(atlas_width, row_width)
            atlas_height += row_height
            row_width = 0
            row_height = 0

        packed_positions.append((row_width, atlas_height))  # 记录左上角位置
        row_width += img.width
        row_height = max(row_height, img.height)

    atlas_width = max(atlas_width, row_width)
    atlas_height += row_height

    # 创建纹理图集
    atlas = Image.new("RGBA", (atlas_width, atlas_height), (0, 0, 0, 0))

    # 合成纹理图集，并生成元数据
    metadata_lines = []
    for (image_number, img), (x1, y1) in zip(images, packed_positions):
        atlas.paste(img, (x1, y1))  # 将图片粘贴到图集上
        width, height = img.size
        metadata_lines.append(f"{image_number}-({x1}, {y1}, {width}, {height})")

    # 保存纹理图集
    atlas.save(output_atlas)

    # 保存元数据
    with open(output_metadata, "w") as f:
        f.write("\n".join(metadata_lines))

    print(f"Texture atlas saved to {output_atlas}")
    print(f"Metadata saved to {output_metadata}")


# 输入与输出配置
input_folder = r""  # 包含数字命名图片的文件夹路径
origin_file = r""  # 每张图片的原点坐标文件
output_atlas = r""  # 输出纹理图集路径
output_metadata = r""  # 输出元数据路径

# 执行函数
pack_images_with_metadata(input_folder, origin_file, output_atlas, output_metadata)

```

3. 通过JPEX，手动确定每个Sprite的源点坐标，设置在裁切脚本中；

4. 手动分区，保存在section.txt中

人物、特效、StartUI等需要循环播放图片实现动画效果的，都采用这样的方式处理素材，在程序加载时读取这些txt文件。

## 人物动画

人物通过updateSprite方法实现动画循环播放和贴图切换，并且设置单独的贴图更新帧率，独立于游戏的70帧，贴图播放仅有30帧，使动画更自然。

Game的update方法会记录每次调用该方法的间隔时间deltaTime，传给updateSprite方法，Character类中有一个成员变量elapsedTime通过累加每次的deltaTime记录过去的时间，当过去的时间超过0.034秒后，触发贴图切换，根据人物当前的状态选择不同的区间，自增帧号，再通过类似段寻址的方式，以区间起始+帧号作为索引，获得纹理图集的锚框和源点坐标，设置给Sprite，特殊的状态还会根据当前帧号大小触发特效、暂停、语音、震屏。当单播类型的动画帧结束后，还会触发状态转移，转移到循环播放的状态。

贴图切换后，根据Character中的bool left变量，对sprite进行方向设定，最后设置位置，完成贴图切换。

为了实现人物被埋的效果（Gaara的W大招），设置Default状态，Default状态不参与任何按键逻辑，贴图为特殊的0号，透明，表示消失。

## 特效动画

动画实现方式与人物动画类似。

对于持续存在直到离开画面的特效，采用循环播放，对于具有持续时间的特效，采用单次播放：

特效结束后，会重置为Default状态，实现复用。

### 特效池

特效位于特效池EffectPool中，人物通过特效池提供的run方法生成分体战斗特效。

特效池包含一个Effect指针容器，在人物的构造函数中完成初始化，通过多态将子类NarutoSEffect、GaaraEffect或DefaultEffect的指针装入特效池的Effect指针容器中，通过run、render、update方式集中处理特效池中的特效。

渲染时，调用特效池EffectPool的render方法，绘制池中非Default状态的特效，特效池的update方法也只更新池中非Default状态的特效。

### 战斗特效

战斗特效是人物在战斗中打出的离体攻击，有追身、运动两种类型。

追身特效有Gaara的W远攻、大招、S大招，能够突然出现在敌方的位置对敌方进行攻击，难以被闪避。

运动特效类似于子弹，能够离体运动，具有直线飞行、对角线飞行两种运动方式，能对敌方造成伤害。

其中，大招特效还具有before、after、miss三种状态，对应击中前、击中后、未击中三种状态，通过updateSprite方法实现状态转移。

战斗特效有NarutoSEffect和GaaraEffect两类，对应两个人物的战斗特效，人物在updateSprite中，播放到特定动画帧时，通过特效池的run方法触发战斗特效：

### 通用特效

通用特效包含：在地面冲刺时的灰尘、在空中冲刺时的烟气、落地时的灰尘、是放大招的闪光特效。

在Character类中以单独一个特效池defaultEffectPool存放，在冲刺、落地、释放大招时通过run方法触发。

## 状态转移

游戏大范围使用状态机思想，包含GameState、CharacterState、EffectState三类状态，对应游戏状态、人物状态、特效状态，其中CharacterState和EffectState对齐。

人物具有38种状态，具体为：

| CharacterState | 对应状态       | CharacterState | 对应状态     | CharacterState | 对应状态    |
| -------------- | -------------- | -------------- | ------------ | -------------- | ----------- |
| Default        | 消失           | Stand          | 站立         | U              | 远攻中      |
| KI\_before     | 空中大招命中前 | Running        | 跑动         | U\_after       | 远攻命中后  |
| KI\_after      | 空中大招命中后 | Jumping        | 跃起         | WUU            | 二段W远攻   |
| KI\_miss       | 空中大招未命中 | Fall           | 下落         | SUU            | 二段S远攻   |
| I\_before      | 大招未命中     | Landed         | 着陆         | WU             | W远攻       |
| I\_after       | 大招命中       | S              | 防御         | SU             | S远攻       |
| I\_miss        | 大招未命中     | S\_Release     | 防御释放中   | Flash          | 冲刺        |
| WI\_before     | W大招命中前    | WJ             | W普攻        | J2             | 普攻2段     |
| WI\_after      | W大招命中后    | SJ             | S普攻        | J3             | 普攻3段     |
| WI\_miss       | W大招未命中    | J1             | 普攻1段      | J4             | 普攻4段     |
| KU             | 空中远攻       | KU\_down       | 空中远攻着陆 | KJ             | 空中普攻    |
| Hit            | 受击硬直       | Kick           | 击飞         | SI\_before     | S大招命中前 |
| SI\_after      | S大招命中后    | SI\_miss       | S大招未命中  |                |             |

人物状态汇总表

Effect另外多出4种：Flash\_air, Flash\_ash, Landed\_ash, I\_effect。

状态转移发生在：交互层触发的行为方法中、贴图更新中、碰撞检测中。整体的人物状态转换图如下：

## 碰撞检测

### 人物与人物碰撞

本游戏尽量避免人物重合，当人物没有攻击，而是相互靠近并发生碰撞时，不会发生重合和穿越，会互相阻挡，产生推动效果。

此时只需要计算出图片的矩形区域，以sf::FloatRect类型保存，并调用intersact方法即可判断是否重合。

如果出现重合，人物的运动速度会降低，同时调用separate方法，以类似库仑力的效果使角色之间相斥，相斥速度计算式为 ，REPULSION为斥力常数，由于人物不设置重量，故将库仑力计算式的分子部分合并为一个斥力常数，分母由于始终大于1，用一次方替代二次方，能够实现间距越小，斥力越大。在人物都挤在墙角时，可以实现平滑地将对方挤出，而非生硬地瞬间位移。

### 人物与特效碰撞

战斗特效，以下也称为人物的“攻击部”，也就是能够对敌方造成伤害的部分。

许多招式的攻击部分和人物本身绘制在同一张图片中，如下例所示：

![人物与其攻击部于同一张图片的示例](https://www.helloimg.com/i/2024/12/20/676526b8b75c9.png)

此时需要对人物本体和攻击部做出划分，正确地判定碰撞。

对于我爱罗，通过观察发现绝大部分的攻击图片，其本体都在图片左侧，攻击部在右侧。所以设定宽40，高50的矩形作为本体框，右侧部分作为攻击部，分别参与碰撞判定。

比如，当判定仙鸣是否被我爱罗的攻击部命中时，需要计算出仙鸣目前的本体部分以及我爱罗的攻击部，用这两者来进行碰撞判定，而不是简单地判断图片是否重合。

对于仙鸣，我爱罗的规律不再适用，仙鸣的攻击分布可分为三类：（以1P键位指代招式）

* 攻击部位于图片右部：KJ、SUU、WJ、KU

![攻击部位于右侧的示例](https://www.helloimg.com/i/2024/12/20/676526b89057e.png)

* 攻击部在图片右上部：WU、WUU

![攻击部位于右上部的示例](https://www.helloimg.com/i/2024/12/20/676526b8633f0.png)

* 攻击部占满整个图片：WI、SJ、J等

![攻击部占满整个图片的示例](https://www.helloimg.com/i/2024/12/20/676526bb0e8b1.png)

于是有以下划分：

```cpp
// 对于NarutoS，KJ SUU WJ KU取除体右段，WU WUU取右上角，其他全匹配
if (enemy->currentState == CharacterState::KJ ||
    enemy->currentState == CharacterState::SUU || 
    enemy->currentState == CharacterState::WJ || 
    enemy->currentState == CharacterState::KU) { // 左裁40
    if (!enemy->left) {
        enemyRect.left += 40.f;
    }
    enemyRect.width -= 40.f;
}
else if (enemy->currentState == CharacterState::WU ||
         enemy->currentState == CharacterState::WUU) {// 左裁35，下裁40
    enemyRect.height -= 40.f;
    if (!enemy->left) {
        enemyRect.left += 35.f;
    }
    enemyRect.width -= 35.f;
}
```

### 人物与地图碰撞

人物本身具有一个sf::Vector2f类型的位置变量position，分为x分量和y分量，代表相对于绝对2D世界左上角的xy坐标，在绘制时，position点需要与图片的origin（素材整理阶段确定的源点）保持相对位置不变，才能避免抽搐。

但是，position不能直接与origin重合，因为每张图片的origin大多位于人物本体的中心，如果与position重合，会导致人物绘制出来不是站在平台上，而是“挂”在了平台上。

所以，需要得到一个适用于大部分图片的偏移量，使position点绘制的部位为人物本体的脚底。

得到该偏移量后，为了避免修改源程序，故编写Python脚本，统一修改origin.txt的y坐标，使其增加。

```python
def adjust_y_coordinate(input_file, output_file, y_increment=25):
    with open(input_file, 'r', encoding='utf-8') as file:
        lines = file.readlines()

    updated_lines = []
    for line in lines:
        line = line.strip()
        if '-' in line:
            # 拆分图号和坐标
            key, value = line.split('-')
            value = value.strip('()')
            x, y = map(int, value.split(', '))
            # 增加 y 坐标
            y += y_increment
            updated_lines.append(f"{key}-({x}, {y})")

    # 保存到新文件
    with open(output_file, 'w', encoding='utf-8') as file:
        file.write('\n'.join(updated_lines))

input_file = r""
output_file = r""
adjust_y_coordinate(input_file, output_file)

print(f"处理完成！结果已保存到 {output_file}")
```

<center>批量修改origin.txt的Python脚本</center>

修改origin.txt后，人物的参照点变为脚底，不仅方便绘制，而且方便计算本体框。

判断与地图平台碰撞只需要在每次更新时遍历所有平台，判断人物的position是否位于平台上方极近距离内。

由于人物下落速度过快时可能导致在相邻两次更新间直接越过平台的判定区域，所以我限制了最大下落速度，并以此作为最大下落速度设置平台的判定距离。

当触发主动下落操作（S+K）时，通过令人物垂直位置增加一个略大于TOLERANCE的距离即可落下当前平台。

## 镜头跟随

镜头跟随是本游戏的一大主要亮点和难点，主要依赖SFML的视图（View）机制实现。

不同于其他2D游戏，如酷跑类、地图类等的镜头永远跟随单个角色、角色在画面中的相对位置永远不变等简单机制。

本游戏具有两个角色，对镜头的移动都具有话语权，本游戏的地图虽然是固定不变的，但是窗口远小于整个地图，窗口具有镜头效果，只展示地图的一部分，具体机制如下：

* 远景永远不动，铺满镜头作为背景；

* 两角色的连线中点作为镜头的焦点；

* 在一定距离内，镜头宽度不变；
* 角色尝试分离并离开镜头区域，镜头区域宽度增加以装下角色，同时镜头焦点变化；
* 镜头达到最大放大程度，不再放大，同时限制角色离开镜头区域；

* 角色靠近，镜头缩小，镜头两侧与角色的间距不变(约1/10宽度，平滑)，直到进入一定距离，缩放达到最大程度，角色很靠近，且具有放大效果。
* 镜头的放缩都采用线性插值实现平滑移动，避免高速运动时的镜头剧烈变化

机制参考了[2D视角游戏镜头机制研究（二）：镜头的部署和移动方式-网易游学-为热爱赋能](https://game.academy.163.com/course/careerArticle?course=438)

### 不跟随镜头元件

游戏具有绝对的2D世界坐标系，独立于产生的窗口，地图中的建筑、人物、特效就采用绝对2D世界坐标系，固定不动，不随镜头变化而改变位置。

绘制时就采用绝对坐标

### 跟随镜头元件

血条、气条、Chakra条等战斗UI需要时刻位于窗口的固定位置，所以需要指定每个元件在窗口中的相对位置，并每帧实时计算这些相对位置的绝对位置。

## 打击感

本游戏是格斗类游戏，营造打击感非常重要，本游戏通过三个方面营造打击感，分别是震屏、顿帧、音效。三种效果都采用事件队列机制实现。

### 震屏

在5.6 镜头跟随的基础上，屏幕震动不难实现，只需要使镜头发生抖动即可。

具体实现方式为：

角色受击后，向自己的事件队列中加入震屏事件🡪Game的业务层处理角色的事件队列，根据事件触发震屏，产生随机的垂直方向偏移量🡪业务层更新视图（View）时应用震屏偏移量，实现视图抖动。

### 顿帧

顿帧代表受击的瞬间暂停一会，营造一种“卡肉感”和“阻滞感”。

暂停可以通过在update层跳过人物的update方法实现，具体实现方法是：

角色受击后，向自己的暂停事件队列中加入事件，表示发出暂停请求🡪Game的update层在更新人物前先处理暂停事件🡪如果是全局暂停，则跳过1P和2P的update方法，使其维持现状🡪当暂停计时器到点后，取消暂停状态，恢复对1P和2P的update方法执行。

### 打击感音效

本游戏共有21种音效，包含人物语音，招式音效和打击音效，打击感音效主要有受击音效和击飞音效。

音效播放依赖于SFML的Sound类，SFML的Sound类和Music类都能使用单独的线程播放音乐和音效，方便了程序的编写，本游戏的主要实现方式为：

角色向自己的音效事件队列audioEventQueue中加入特定的音效事件，表示请求播放音效🡪Game类的update方法处理音效事件，根据队列中的请求播放对应的音效。

## 键位设置

本游戏招式繁多，每个玩家能够使用9个键位操纵角色，共有15种操作方式，详见2.2 游戏操作方式。下面主要介绍如何实现各种键位操作：

### 长按、短按

SFML提供两种键盘监听方式：

| 方式         | 优点                                                         | 缺点                                             |
| ------------ | ------------------------------------------------------------ | ------------------------------------------------ |
| 键盘事件队列 | 能够区分按下次数，长按也只算一次按键，避免单次按键多次判定；  能够识别按键释放事件； | 原子性过高，无法识别多个键是否被同时按下；       |
| 实时监听     | 灵敏，能够实现组合键；                                       | 过于灵敏，单次按键会多次判定  只能监听是否按下； |

SFML键盘监听方式分析表

由于本游戏无法放弃组合键机制，所以只能使用实时监听方式。

单次按键多次判定会导致：在一瞬间触发多次跳跃，浪费次数，无法实现二段跳效果；在一瞬间普攻十几次，无法实现多段普攻。

针对这两个问题，解决方案如下：

对二段跳设置速度限制，起跳是初速度向上的匀减速运动，为了防止在短时间内连续触发跳跃，限制起跳时的速度不能太快，等到首段跳跃的向上速度减速到一定程度后，再开放二段起跳的功能：

程序中的“LIMIT\_V”为起跳初速度JUMP\_VELOCITY + 0.1秒的重力GRAVITY减速，0.1秒是实测得到的连续两次点按键盘的最短间隔时间。

普攻同样设置触发限制，通过动画帧号限制多段普攻的触发，如果第一段普攻只播放了一两帧（每帧动画0.034秒），却导致了多次J键判定，那么由于帧号不足，将被屏蔽，由此实现多段普攻。

仙鸣的二段WU和二段SU同理。

### 组合键

对于游戏中的组合键，通过设置父子状态的方式实现，以SJ举例：

首先监听S是否按下，如果没有按下，则不进入“S”系列招式（S、SJ、SU、SI等）的进一步判定，如果按下，则进入“S”系列招式的进一步判定，判定J是否按下，如果按下并通过状态限制后，则调用sj()方法，触发S普攻招式。区分SJ和J的方式为：

当S按下，则为SJ，当S未被按下，再检测J键，此时判定是否进行普攻。

游戏还具有抗打断机制，即释放部分招式时无法左右移动、跳跃从而打断招式释放。主要通过角色当前状态来屏蔽移动、跳跃操作，只需要加一个if判断状态即可。

## 战斗效果

本游戏作为格斗游戏，具有前摇、后摇、大招时停动画、受击硬直、击飞等丰富的战斗效果。

### 前摇、后摇

前摇、后摇指人物释放技能前、后不可打断，脱离控制的行为，主要用于向敌方提供反应时间和攻击窗口期。如果人物能够无前摇、后摇地释放技能，那么将导致无法近身攻击，只需要一直不停地释放技能就能产生“金钟罩”从而立于不败之地，对游戏性产生很大影响。

最初，前摇和后摇机制计划使用针对角色的局部暂停来实现，在角色释放技能前后添加暂停，屏蔽键盘输入，达到一瞬间的不可控状态，但是过于繁琐。

最终的解决方法为：将人物的38种状态做区分，有非攻击态和攻击态，当角色处于攻击态时，屏蔽特定的键盘输入，同时增加技能前后的相同动画帧，拉长动画播放时间，就形成了前摇和后摇。以下以Gaara的SJ技能举例：

![招式前摇、后摇动画帧分区示意图（Gaara的S普攻）](https://www.helloimg.com/i/2024/12/20/676526bb785b1.png)

### 大招时停动画

Gaara的三种大招都是瞬发，没有设置时停和黑屏动画。但是仙鸣的大招具有很长的前摇动画，如果全部作为前摇播放，将大大削弱角色的战斗力和动画的表现力。

所以需要为仙鸣设置大招时停动画，具体包含：

* 仙鸣大招前摇期间，背景全黑突出人物；
* 除仙鸣本体之外，其他人物、特效全部暂停；
* 大招释放瞬间，人物周围出现蓝色闪光特效，播放大招对应人物语音；
* 大招前摇结束后，恢复正常更新；

结合已经实现的暂停器pause、通用特效池defaultPool、音效触发器gameAudio，只需要额外实现背景黑屏即可。实现方式为：为Game类添加一个专门的黑色背景sprite，如果处于部分暂停期间，则不绘制地图，而是绘制黑色背景。

### 受击硬直、击飞

游戏设置了受击的硬直时间和击飞效果。

受击硬直的特点是：持续时间内无法操控，能够被再次攻击，能够以正常的物理规律运动。

击飞的特点是：持续时间内无法操控，不能被再次击中。

受击硬直主要用于供对手打出连招，而击飞则用于限制对手无法一直连击。

在代码中，击飞对应Kick状态，受击对应Hit状态。当处于这两个状态时，键盘控制会被屏蔽，无法释放招式或移动跳跃；刚进入状态时，会触发打击音效，击飞状态额外有人物闷哼语音，用于表现打击感。

## 性能优化

性能优化为开发过程中遇到的难点之一，主要的性能问题是：

* 频繁切换sprite的纹理，程序运行时GPU占用率100%
* 每增加一个需要绘制的sprite，每秒执行游戏主体大循环的次数就会减少，导致运行过程中帧率不稳定，表现为游戏过程中的卡顿、掉帧

### 限制帧率

SFML提供了限制窗口帧率的方法，本游戏限制帧率为70帧。该方法限制帧率的机制为：在每次循环后睡眠一段时间，使一秒钟执行的循环总数在70次左右

由于限制之前，游戏的帧率在200~400帧，所以设置的物理体系数值全部出错，表现为人物运动迟缓，速度、加速度都大幅降低。所以通过计算，得到了70帧下适用的各项速度数值，保存在Constant.h中以宏定义形式在代码中使用。

### 纹理图集

如5.1.2 素材整理，编写Python程序，将上千张图片合并为一张图片，称为纹理图集，避免每次更新贴图都要切换sprite的纹理，使GPU使用率从最初的100% 降低到目前的30%左右。

![GPU使用率实测的截图](https://www.helloimg.com/i/2024/12/20/676526b9218a3.png)

# 心得体会

## 游戏开发历程

见[git历史记录](https://github.com/novelyear/bvn/commits/master/)

## 游戏版本迭代

最初设想的版本是单人对战人机，但是从上面的git历史可以看到完成初步narutoAI已经非常靠后了，由于人机实现难度较大，效果不好，于是改为双人游戏版本，能提供更好的游戏体验。

## 结语

四千多行代码，近三千张图片，历时一个月，虽然和真正的游戏相比规模尚小，但已经这是我迄今为止独立写过的最大工程了，每一个小功能都花费了很多精力，许多个小功能才累积成了现在的样子。这也是我首次全程使用git做版本管理，使用多个分支进行工作很有条理。

开发的过程见证了我编码能力的一步步加强，最开始设计能力不足，类结构混乱，代码严重耦合，这也导致最后Character类和Game类显得比较臃肿，难以重构，其中Character类的定义竟然将35种动画的图号区间每个都写为一个成员变量。

后来，我的思路更加清晰，编码更合理，之后的特效类采用哈希表保存大量的动画帧信息；人物、地图、特效的生成充分利用工厂模式等设计模式优化代码结构；事件队列的使用也越来越合理，最开始的震屏事件队列和Character类耦合，之后的暂停事件队列和音效事件队列就与Character类实现解耦。

最初想要将这个项目作为长期项目来做，希望能够用C++重写整个游戏，并且加入自己的一些魔改素材整活。但真正开发后发现，人物之间的区别很多，各有特色，最初设计的Character抽象类并不能满足作为所有人物基类的功能，设计得太“个性化” ，导致后续增加角色困难。所幸Map类还是设计得比较好，扩展很容易。

这个游戏的开发让我把从软件工程课上学到的东西用了出来，设计模式和代码架构对于整个工程的作用的确很巨大。开发到后期，debug也逐渐得心应手，图形化调试不像一般的调试，看不到实时画面，找到问题的难度更大，但是到了后期，解决的问题成为了经验，往往一次调试就能直接找到bug，这表示我对整体有了更清晰的了解。

如果看过项目的素材库[/access](https://github.com/novelyear/bvn/tree/master/access)，就会发现我还有很多没用到的素材，还有很多机制没有实现，相比于原游戏，游戏性还很不足，以后如果有时间，也许会完善机制，实现没有实现的构想。
