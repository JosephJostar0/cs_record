# 存储系统 重要知识点

## 一、主存储器

### DRAM

- 读写周期：DRAM芯片进行两次连续读(写)操作时所必须间隔的时间。

- DRAM电容上的电荷一般只能维持1~2ms，因此每个一定时间必须刷新，通常取2ms，称为刷新周期。
    1. 集中刷新：指在一个刷新周期内，利用一段固定的时间，依次对存储器的所有行进行逐一再生，在此期间停止对存储器的读写操作。优点是读写操作不受刷新工作影响，缺点是集中刷新期间（死区）不能访问存储器。
    2. 分散刷新：把对每行的刷新分散到各个工作周期中。将一个存储器的工作周期分为两部分，前半部分用于正常读写或保持，后半部分用于刷新。优点是没有死区；缺点是加长了系统的存取周期，降低整机速度。
    3. 异步刷新：异步刷新是前两种方法的结合，即可以缩短“死时间”，又能充分利用最大刷新间隔为2ms的特点。将刷新周期除以行数，得到两次刷新操作之间的时间间隔t，利用逻辑电路每隔时间t产生一次刷新请求。这样可以避免使CPU连续等待过长的时间，且减少了刷新次数，从根本上提高了整机工作效率

> DRAM的刷新有几个特点：1.刷新对CPU透明，即刷新不依赖于外部的访问。2.动态RAM的刷新单位是行，由芯片内部自行生成地址。3.刷新操作类似于读操作，但刷新时不需要选片，即整个存储器中的所有芯片同时被刷新。

- DRAM通常采用地址引脚复用技术，行地址和列地址通过相同的引脚分先后两次输入。

### ROM 只读存储器

- ROM和RAM都是支持随机访问的存储器，SRAM和DRAM均为易失性半导体存储器；而ROM是非易失性存储器，即使掉电也不会丢失。

- ROM器件有两个显著的优点：(1)结构简单，位密度高；(2)具有非易失性，可靠性高。

- ROM有以下几类：
    1. MROM掩模式只读存储器  
    MROM的内容由半导体制造厂按用户提出的要求在芯片的生产过程中直接写入，写入后任何人都无法改变其内容。优点是可靠性高、集成性高、价格便宜；缺点是灵活性差。
    2. RROM一次可编程只读存储器  
    PROM是可以实现一次性编程的只读存储器。允许用户利用编程器写入自己的程序，一旦写入，内容就无法改变。
    3. EPROM可擦除可编程只读存储器  
    EPROM不仅可以由用户写入信息，而且可以对其内容进行多次改写，但改写的次数有限。
    4. Flash存储器(闪存)  
    Flash存储器是在EPROM的基础上发展起来的，可以在不加电的情况下长期保存信息，又能在线进行快速擦除与重写。
    5. SSD固态硬盘(Solid State Drives)  
    基于闪存的固态硬盘是用固态电子存储芯片阵列制成的硬盘，由控制单元和存储单元(Flash)组成。读写速度快、功耗低，但价格高。

### 主存储器的基本组成

- 现代计算机通常采用字节编址方式，此时存储体内的一个地址中有1字节。
- 数据线的宽度与MDR的宽度相同，地址线的宽度与MAR宽度相同。

### 多模块存储器

- 多模块存储器是一种空间并行技术，利用多个结构完全相同的存储模块的并行工作来提高存储器的吞吐率。常用的有 单体多字存储器 和 多体低位交叉存储器。

1. *单体多字存储器*  
   存储器中只有一个存储体，每个存储单元存储m个字，总线宽度也为m个字，地址必须顺序排列并处于同一存储单元。  
   单体多字系统在一个存取周期内，从同一地址取出m条指令，然后将指令逐条送至CPU执行，即每隔1/m存储周期，CPU向主存取一条指令。  
   缺点：指令和数据在主存内必须是连续存放的，一旦遇到转移指令，或操作数不能连续存放，这种方法的效果就不明显。

2. *多体并行存储器*  
    多体并行存储器由多模块组成。每个模块都有相同的容量和存取速度，各模块都有独立的读写控制电路、地址寄存器和数据寄存器。他们技能并行工作，又能交叉工作。  
    多体并行存储器分为高位交叉编址和低位交叉编址两种。  
    1. 高位交叉编址(顺序方式)  
    高位地址表示体号，地位地址为体内地址。  
    高位交叉方式下，总是把低位的体内地址送到由高位体号确定的模块内进行译码。访问一个连续主存块时，总是先在一个模块内访问，不能提高存储器的吞吐率。
    2. 低位交叉编址(交叉方式)  
    低位地址为体号，高位地址为体内地址。  
    低位交叉方式下，总是把高位的体内地址送到低位体号确定的模块内进行译码。采用低位交叉编址后，可在不改变每个模块存取周期的前提下，采用流水线的方式并行存取，提高存储器的带宽。
