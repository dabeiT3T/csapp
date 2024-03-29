## Chapter 6

> 存储器层次结构是可行的，这是因为与下一个更低层次的存储设备相比来说，一个编写良好的程序倾向于更频繁地访问某一个层次上地存储设备。
>
> 如果你的程序需要的数据是存储在 CPU 寄存器中，那么在指令的执行期间，在 0 个周期内就能访问到它们。如果存储在高速缓存中，需要 4~75 个周期。如果存储在主存中，需要上百个周期。而如果存储在磁盘上，需要大约几千万个周期！
>
> 这个思想围绕着计算机程序的一个称为局部性（locality）的基本属性。具有良好局部性的程序倾向于一次又一次地访问相同的数据项集合，或是倾向于访问邻近地数据项集合。
>
> 特别地，我们将注意力集中在高速缓存存储器上，它是作为 CPU 和主存之间的缓存区域，因为它们对应用程序性能的影响最大。你还会学到一种描绘某台机器上存储器层次结构的性能的有趣方法，称为“存储器山（memory mountain）”，它展示出读访问时间是局部性的一个函数。

### 6.1 存储技术

#### 6.1.1 随机访问存储器

> 随机访问存储器（Random-Access Memory，RAM）分为两类：静态的和动态的。静态 RAM（SRAM）比动态RAM（DRAM）更快，但也贵得多。SRAM 用来作为高速缓存存储器，既可以在 CPU 芯片上，也可以在片下。DRAM 用来作为主存以及图形系统的帧缓存区。
>
> 1. 静态 RAM
>
>    SRAM 将每个位存储在一个双稳态的（bistable）存储器单元里。这个电路有这样一个属性，它可以无限期地保持在两个不同的电压配置（configuration）或状态（state）之一。其他任何状态都是不稳定的——从不稳定状态开始，电路会迅速地转移到两个稳定状态中的一个。
>
>    由于 SRAM 存储器单元的双稳态特性，只要有电，它就会永远地保持它的值。
>
> 2. 动态 RAM
>
>    DRAM 将每个位存储为对一个电容的充电。与 SRAM 不同，DRAM 存储器单元对干扰非常敏感。当电容的电压被扰乱之后，它就永远不会恢复了。暴露在光线下会导致电容电压改变。实际上，数码照相机和摄像机中的传感器本质上就是 DRAM 单元的阵列。
>
>    很多原因会导致漏电，使得 DRAM 单元在 10~100 毫秒时间内失去电荷。内存系统必须周期性地读出，然后重写来刷新内存每一位。有些系统也使用纠错码，其中计算机的字会被多编码几个位（例如 64 位的字可能用 72 位来编码），这样一来，电路可以发现并纠正一个字中任何单个的错误位。
>
> 3. 传统的 DRAM
>
>    DRAM 芯片中的单元（位）被分成 d 个超单元（supercell），每个超单元都由 w 个 DRAM 单元组成。一个 d*w 的 DRAM 总共存储了 dw 位信息。
>
>    行地址 i 称为 RAS（Row Access Strobe，行访问选通脉冲）请求。列地址 j 称为 CAS（Column Access Strobe，列访问选通脉冲）请求。
>
>    例如，要从 16*8 的 DRAM 中读出超单元（2，1），内存控制器发送行地址 2。DRAM 的响应是将行 2 的整个内容都复制到一个内部行缓存区。接下来，内存控制器发送列地址 1。DRAM 的响应是从行缓冲区复制出超单元（2，1）中的 8 位，并把它们发送到内存控制器。
>
>    电路设计者将 DRAM 组成成二维阵列而不是线性数组的一个原因是降低芯片上地址引脚的数量。二位阵列组织的缺点是必须分两步发送地址，这增加了访问时间。
>
> 4. 内存模块
>
>    DRAM 芯片封装在内存模块（memory module）中，它插到主板的扩展槽上。Core i7 系统使用的 240 个引脚的双列直插内存模块（Dual Inline Memory Module，DIMM），它以 64 位为块传送数据到内存控制器和从内存控制器传出数据。
>    
>    实例模块用 8 个 64 Mbit 的 8 M*8 的 DRAM 芯片，总共存储 64 MB（兆字节），这 8 个芯片编号为 0~7。每个超单元存储主存的一个字节，而用相应超单元地址为（i，j）的 8 个超单元来表示主存中字节地址 A 处的 64 位字。DRAM 0 存储第一个（低位）字节，DRAM 1 存储下一个字节，依此类推。
>    
> 5. 增强的 DRAM
>
>    - 快页模式 DRAM（Fast Page Mode，FPM DRAM）。传统的 DRAM 将超单元的一整行复制到它的内部行缓冲区中，使用一个，然后丢弃剩余的。FPM DRAM 允许对同一行连续地访问可以直接从行缓冲区得到服务，从而改进了这一点。
>    - 扩展数据输出 DRAM（Extended Data Out DRAM，EDO DRAM）。FPM DRAM 的一个增强的形式，它允许各个 CAS 信号在时间上靠得更紧密一点。
>    - 同步 DRAM（Synchronous DRAM，SDRAM）。就它们与内存控制器通信使用一组显式的控制信号来说，常规的，FPM 和 EDO DRAM 都是异步的。SDRAM 用与驱动内存控制器相同的外部时钟信号的上升沿来代替许多这样的控制信号。最终效果就是 SDRAM 能够比那些异步的存储器更快地输出它地超单元地内容。
>    - 双倍数据速率同步 DRAM（Double Data-Rate Synchronous DRAM，DDR SDRAM）。DDR SDRAM 是对 SDRAM 的一种增强，它通过使用两个时钟沿作为控制信号，从而使 DRAM 的速度翻倍。不同类型的 DDR SDRAM 是用提高有效带宽的很小的预取缓冲区的大小来划分的：DDR（2 位）、DDR2（4 位）和 DDR3（8 位）。
>    - 视频 RAM（Video RAM，VRAM）。它用在图形系统的帧缓冲区中。VRAM 的思想与 FPM DRAM 类似。VRAM 允许对内存并行地读和写。因此，系统可以在写下一次更新的新值（写）的同时，用帧缓冲区中的像素刷屏幕（读）。
>
> 6. 非易失性存储器
>
>    如果断电，DRAM 和 SRAM 会丢失它们的信息，从这个意义上说，它们是易失的（volatile）。另一方面，非易失性存储器（nonvolatile memory）即使是在关电后，依然保存着它们的信息。由于历史原因，虽然 ROM 中有的类型既可以读也可以写，但是它们整体上都被称为只读存储器（Read-Only Memory，ROM）。ROM 是以它们能够被重编程（写）的次数和对它们进行重编程所用的机制来区分的。
>
>    PROM（Programmable ROM，可编程 ROM）只能被编程一次。PROM 的每个存储器单元有一种熔丝（fuse），只能用高电流熔断一次。
>
>    可擦写可编程 ROM（Erasable Programmable ROM，EPROM）有一个透明的石英窗口，允许光到达存储单元。紫外线光照射过窗口，EPROM 单元就被清除为 0。对 EPROM 编程是通过使用一种把 1 写入 EPROM 的特殊设备来完成的。EPROM 能够被擦除和重编程的次数的数量级可以达到 1000 次。电子可擦除 PROM（Electrically Erasable PROM，EEPROM）类似于 EPROM，但是它不需要一个物理上独立的编程设备，因此可以直接在印制电路卡上编程。EEPROM 能够被编程的次数的数量级可以达到 10^5 次。
>
>    闪存（flash memory）是一类非易失性存储器，基于 EEPROM，它已经成为了一种重要的储存技术。我们会仔细研究一种新型的基于闪存的磁盘驱动器，称为固态硬盘（Solid State Disk，SSD），它能提供相对于传统旋转磁盘的一种更快速、更强健和更低能耗的选择。
>
>    存储在 ROM 设备中的程序通常被称为固件（firmware）。当一个计算机系统通电以后，它会运行存储在 ROM 中的固件。
>
> 7. 访问主存
>
>    数据流通过称为总线（bus）的共享电子电路在处理器和 DRAM 主存之间来来回回。每次 CPU 和主存之间的数据传送都是通过一系列步骤来完成的，这些步骤称为总线事务（bus transaction）。读事务（read transaction）从主存传送数据到 CPU。写事务（write transaction）从 CPU 传送数据到主存。
>
>    主要部件是 CPU 芯片、我们将称为 I/O 桥接器（I/O bridge）的芯片组（其中包括内存控制器），以及组成主存的 DRAM 内存模块。这些部件由一对总线连接起来，其中一条总线是系统总线（system bus），他连接 CPU 和 I/O 桥接器，另一条总线是内存总线（memory bus），他连接 I/O 桥接器和主存。I/O 桥接器将系统总线的电子信号翻译成内存总线的电子信号。I/O 桥也将系统总线和内存总线连接到 I/O 总线，像磁盘和图形卡这样的 I/O 设备共享 I/O 总线。

#### 6.1.2 磁盘存储

> 1. 磁盘构造
>
>    磁盘是由盘片（platter）构成的。每个盘片有两面或者称为表面（surface），表面覆盖着磁性记录材料。盘片中央有一个可以旋转的主轴（spindle），它使得盘片以固定的旋转速率（rotational rate）旋转，通常是 5400~15000 转每分钟（Revolution Per Minute，RPM）。磁盘通常包含一个或多个这样的盘片，并封装在一个密封的容器内。
>
>    每个表面是由一组称为磁道（track）的同心圆组成的。每个磁道被划分为一组扇区（sector）。每个扇区包含相等数量的数据位（通常是 512 字节），这些数据编码在扇区上的磁性材料中。扇区之间由一些间隙（gap）分隔开，这些间隙中不存储数据位。间隙存储用来标识扇区的格式化位。
>
>    磁盘制造商通常用术语柱面（cylinder）来描述多个盘片驱动器的构造，这里，柱面是所有盘片表面上到主轴中心的距离相等的磁道的集合。
>
> 2. 磁盘容量
>
>    磁盘容量是由以下技术因素决定的：
>
>    - 记录密度（recording density）（位/英寸）：磁道一英寸的段中可以放入的位数。
>    - 磁道密度（track density）（道/英寸）：从盘片中心出发半径上一英寸的段内可以有磁道数。
>    - 面密度（areal density）（位/平方英寸）：记录密度与磁道密度的乘积。
>
>    现代大容量磁盘使用一种称为多区记录（multiple zone recording）的技术，在这种技术中，柱面的集合被分割成不相交的子集合，称为记录区（recording zone）。每个区包含一组连续的柱面。一个区中的每个柱面中的每条磁道都有相同数量的扇区，这个扇区的数量是由该区中最里面的磁道所能包含的扇区数确定的。
>
>    下面的公式给出了一个磁盘的容量：
>    $$
>    磁盘容量=\frac{字节数}{扇区}\times\frac{平均扇区数}{磁道}\times\frac{磁道数}{表面}\times\frac{表面数}{盘片}\times\frac{盘片数}{磁盘}
>    $$
>    注意，制造商是以千兆字节（GB）或兆兆字节（TB）为单位来表达磁盘容量的，这里 1 GB = 10^9 字节，1 TB = 10^12 字节。
>
>    **一千兆字节有多大**
>
>    对于与 DRAM 和 SRAM 容量相关的计量单位，通常 K = 2^10，M = 2^20，G = 2^30，而 T = 2^40。对于与像磁盘和网络这样的 I/O 设备容量相关的计量单位，通常 K = 10^3，M = 10^6，G = 10^9，而 T = 10^12。速率和吞吐量常常也使用这些前缀。
>
> 3. 磁盘操作
>
>    磁盘用读/写头（read/write head）来读写存储在磁性表面的位，而读写头连接到一个传动臂（actuator arm）一端。通过沿着半径轴前后移动这个传动臂，驱动器可以将读/写头定位在盘面上的任何磁道上。这样的机械运动称为寻道（seek）。有多个盘片的磁盘针对每个盘面都有一个独立的读/写头。读/写头垂直排列，一致行动。在任何时刻，所有的读/写都位于同一个柱面上。
>
>    在传动臂末端的读/写头在磁盘表面高度大约 0.1 微米处的一层薄薄的气垫上飞翔，速度大约为 80 km/h。在这样小的间隙里，盘面上一粒微小的灰尘都像一块巨石。如果读/写头碰到了这样的一块巨石，读/写头会停下来，撞到盘面——所谓的读/写头冲撞（head crash）。
>
>    磁盘以扇区大小的块来读写数据。对扇区的访问时间（access time）有三个主要的部分：寻道时间（seek time）、旋转时间（rotational latency）和传送时间（transfer time）：
>
>    - 寻道时间：为了读取某个目标扇区的内容，传动臂首先将读/写头定位到包含目标扇区的磁道上。移动传动臂所需的时间称为寻道时间。寻道时间 T~seek~ 依赖于读/写头以前的位置和传动臂在盘面上移动的速度。现代驱动器中平均寻道时间 T~avg_seek~ 是通过对几千次对随机扇区的寻道求平均值来测量的，通常为 3~9 ms。一次寻道的最大时间 T~max_seek~ 可以高达 20 ms。
>
>    - 旋转时间：一旦读/写头定位到了期望的磁道，驱动器等待目标扇区的第一个位旋转到读/写头下。这个步骤的性能依赖于读/写头到达目标扇区时盘面的位置以及磁盘的旋转速度。在最坏的情况下，读/写头刚刚错过了目标扇区，必须等待磁盘转一整圈。因此，最大旋转延迟（以秒为单位）是
>      $$
>      T_{max\ rotation} = \frac{1}{RPM}\times\frac{60s}{1min}
>      $$
>      平均旋转时间 T~avg_rotation~ 是 T~max_rotation~ 的一半。
>
>    - 传送时间：当目标扇区的第一个位位于读/写头下时，驱动器就可以开始读或者写该扇区的内容了。一个扇区的传送时间依赖于旋转速度和每条磁道的扇区数目。因此，我们可以粗略地估计一个扇区以秒为单位地平均传送时间如下
>      $$
>      T_{avg\ transfer} = \frac{1}{RPM}\times\frac{1}{平均扇区数/磁道}\times\frac{60s}{1min}
>      $$
>
>    例子说明了一些很重要的问题：
>
>    - 访问一个磁盘扇区中 512 字节的时间主要是寻道时间和旋转延迟。访问扇区中的第一个字节用了很长时间，但是访问剩下的字节几乎不用时间。
>    - 因为寻道时间和旋转延迟大致相等，所以将寻道时间乘 2 是估计磁盘访问时间的简单而合理的方法。
>    - 对存储在 SRAM 中的一个 64 位字的访问时间大约是 4ns，对 DRAM 的访问时间是 60ns。因此，从内存中读一个 512 字节扇区大小的块的时间对 SRAM 来说大约是 256ns，对 DRAM 来说大约是 4000ns。磁盘访问的时间，大约 10ms，是 SRAM 的大约 40000 倍，是 DRAM 的大约 2500 倍。
>
> 4. 逻辑磁盘块
>
>    磁盘封装中有一个小的硬件/固件设备，称为磁盘控制器，维护着逻辑块号和实际（物理）磁盘扇区之间的映射关系。
>
>    当操作系统想要执行一个 I/O 操作时，例如读一个磁盘扇区的数据到主存，操作系统会发送一个命令到磁盘控制器，让它读某个逻辑块号。控制器上的固件执行一个快速表查找，将一个逻辑块号翻译成一个（盘面，磁道，扇区）的三元组，这个三元组唯一地标识了对应的物理扇区。控制器上的硬件会解释这个三元组，将读/写头移动到适当的柱面，等待扇区移动到读/写头下，将读/写头感知到的位放到控制器上的一个小缓冲区中，然后将它们复制到主存中。
>
>    **格式化的磁盘容量**
>
>    格式化包括用标识扇区的信息填写扇区之间的间隙，标识出表面有故障的柱面并且不使用它们，以及在每个区中预留出一组柱面作为备用，如果区中一个或多个柱面在磁盘使用过程中坏掉了，就可以使用这些备用柱面。因为存在着这些备用的柱面，所以磁盘制造商所说的格式化容量比最大容量要小。
>
> 5. 连接 I/O 设备
>
>    例如图形卡、监视器、鼠标、键盘和磁盘这样的输入/输出（I/O）设备，都是通过 I/O 总线，例如 Intel 的外围设备互联（Peripheral Component Interconnect，PCI）总线连接到 CPU 和主存的。系统总线和内存总线是与 CPU 相关的，与它们不同，诸如 PCI 这样的 I/O 总线设计成与底层 CPU 无关。
>
>    - 通用串行总线（Universal Serial Bus，USB）控制器是一个连接到 USB 总线的设备的中转机构；USB 3.0 总线的最大带宽为 625 MB/s。USB 3.1 总线的最大带宽为 1250 MB/s。
>    - 图形卡（或适配器）包含硬件和软件逻辑，它们负责代表 CPU 在显示器上画像素。
>    - 主机总线适配器将一个或多个磁盘连接到 I/O 总线，使用的是一个特别的主机总线接口定义的通信协议。两个最常用的这样的磁盘接口是 SCSI 和 SATA。SCSI 磁盘通常比 SATA 驱动器更快但是也更贵。SCSI 主机总线适配器（通常称为 SCSI 控制器）可以支持多个磁盘驱动器，与 SATA 适配器不同，它只能支持一个驱动器。
>
> 6. 访问磁盘
>
>    CPU 使用一种称为内存映射 I/O（memory-mapped I/O）的技术来向 I/O 设备发射命令。在使用内存映射 I/O 的系统中，地址空间中有一块地址是与 I/O 设备通信保留的。每个这样的地址称为一个 I/O 端口（I/O port）。当一个设备连接到总线时，它与一个或多个端口相关联（或它被映射道一个或多个端口）。
>
>    设备可以自己执行读或者写总线事务而不需要 CPU 干涉的过程，称为直接内存访问（Direct Memory Access，DMA）。这种数据传送称为 DMA 传送（DMA transfer）。
>
>    在 DMA 传送完成，磁盘扇区的内容被安全地存储在主存中以后，磁盘控制器通过给 CPU 发送一个中断信号来通知 CPU。基本思想是中断会发信号到 CPU 芯片地一个外部引脚上。这会导致 CPU 暂停它当前正在做地工作，跳转到一个操作系统例程。这个程序会记录下 I/O 已经完成，然后将控制返回到 CPU 被中断地地方。

练习题 6.4

在最好的情况中，块被映射到连续的扇区，在同一柱面上，那样就可以一块接一块地读，不用移动读/写头。

通过勘误表验证，1 MB 文件需要 2048 个 512 字节地逻辑块组成；所以，

A. T~total~ = T~avg_seek~ + T~avg_rotation~ + 2 * T~max_rotation~ + T~48/1000_max_rotation~

B. T~total~ = (T~avg_seek~ + T~avg_rotation~) * 2048 + 2 * T~max_rotation~ + T~48/1000_max_rotation~

#### 6.1.3 固态硬盘

> 固态硬盘（Solid State Disk，SSD）是一种基于闪存的存储技术。一个 SSD 封装由一个或多个闪存芯片和闪存翻译层（flash translation layer）组成，闪存芯片替代传统旋转磁盘中的机械驱动器，而闪存翻译层是一个硬件/固件设备，扮演与磁盘控制器相同的角色，将对逻辑块的请求翻译成对底层物理设备的访问。
>
> 注意，读 SSD 比写要快。随机读和写的性能差别是由底层闪存基本属性决定的。一个闪存由 B 个块的序列组成，每个块由 P 页组成。通常，页的大小是 512 字节 ~ 4KB，块是由 32~128 页组成的，块的大小为 16KB~512KB。数据是以页为单位读写的。只有在一页所属的块整个被擦除之后，才能写这一页（通常是指该块中的所有位都被设置成 1）。不过，一旦一个块被擦除了，块中每一个页都可以不要再进行擦除就写一次。在大约进行 100000 次重复写之后，块就会磨损坏。一旦一个块磨损坏之后，就不能再使用了。
>
> 随机写很慢，有两个原因。首先，擦除块需要相对较长的时间，1ms 级的，比访问页所需时间要高一个数量级。其次，如果写操作试图修改一个包含已经有数据（也就是不是全为 1）的页 p，那么这个块中所有带有有用数据的页都必须被复制到一个新（擦除过的）块，然后才能进行对页 p 的写。

#### 6.1.4 存储技术趋势

> 这些惊人的长期趋势突出了内存和磁盘技术的一个基本事实：增加密度（从而降低成本）比降低访问时间容易得多。
>
> 直到 2003 年左右多核处理器的出现，这个性能差距都是延迟的函数，DRAM 和磁盘的访问时间比单个处理器的周期时间提高得更慢。不过，随着多核的出现，这个性能越来越成为了吞吐量的函数，多个处理器核并发地向 DRAM 和磁盘发请求。
>
> 现代计算机频繁地使用基于 SRAM 的高速缓存，试图弥补处理器 - 内存之间的差距。这种方法行之有效是因为应用程序的一个称为局部性（locality）的基本属性。
>
> **当周期时间保持不变：多核处理器的到来**
>
> 发现他们无法再像以前一样迅速地增加 CPU 的时钟频率了，因为如果那样芯片的功耗会太大。解决方法是用多个小处理器核（core）取代单个大处理器，从而提高性能，每个完整的处理器能够独立地、与其他核并行地执行程序。

### 6.2 局部性

> 一个编写良好的计算机程序常常具有良好地局部性（locality）。也就是，它们倾向于引用邻近于其他最近引用过的数据项的数据项，或者最近引用过的数据项本身。这种倾向性，被称为局部性原理（principle of locality），是一个持久的概念，对硬件和软件系统的设计和性能都有着极大的影响。
>
> 局部性通常有两种不同的形式：时间局部性（temporal locality）和空间局部性（spatial locality）。在一个具有良好时间局部性的程序中，被引用过一次的内存位置很可能在不远的将来再被多次引用。在一个具有良好空间局部性的程序中，如果一个内存位置被引用了一次，那么程序很可能在不远的将来引用附近的一个内存位置。
>
> 一般而言，有良好局部性的程序比局部性差的程序运行得更快。

#### 6.2.1 对程序数据引用的局部性

> 我们说顺序访问一个向量每个元素的函数，具有步长为 1 的引用模式（stride-1 reference pattern）（相对于元素的大小）。有时我们称步长为 1 的引用模式为顺序引用模式（sequential reference pattern）。一个连续向量中，每隔 k 个元素进行访问，就称为步长为 k 的引用模式（stride-k reference pattern）。步长为 1 的引用模式是程序中空间局部性常见和重要的来源。一般而言，随着步长的增加，空间局部性下降。

#### 6.2.2 取指令的局部性

> for 循环体里的指令是按照连续的内存顺序执行的，因此循环有良好的空间局部性。因为循环体会被执行多次，所以它也有很好的时间局部性。
>
> 代码区别于程序数据的一个重要的属性是在运行时它是不能被修改的。当程序正在执行时，CPU 只从内存中读出它的指令。CPU 很少会重写或修改这些指令。

#### 6.2.3 局部性小结

> 量化评价程序中局部性的一些简单原则：
>
> - 重复引用相同变量的程序有良好的时间局部性。
> - 对于具有步长为 k 的引用模式的程序，步长越小，空间局部性越好。
> - 对于取指令来说，循环有好的时间和空间局部性。循环体越小，循环迭代次数越多，局部性越好。
>
> 了解如何看一眼源代码就能获得对程序中局部性的高层次的认识，是程序员要掌握的一项有用而且重要的技能。

### 6.3 存储器层次结构

> 在最高层（L0），是少量快速的 CPU 寄存器，CPU 可以在一个时钟周期内访问它们。接下来是一个或多个小型到中型的基于 SRAM 的高速缓存存储器，可以在几个 CPU 时钟周期内访问它们。然后是一个大的基于 DRAM 的主存，可以在几十到几百个时钟周期内访问它们。接下来是慢速但是容量很大的本地磁盘。

#### 6.3.1 存储器层次结构中的缓存

> 存储器层次结构的中心思想是，对于每个 k，位于 k 层的更快更小的存储设备作为位于 k+1 层的更大更慢的存储设备的缓存。
>
> 第 k+1 层的存储器被划分成连续的数据对象块（chunk），称为块（block）。每个块都有一个唯一的地址或名字，使之区别于其他的块。块可以是固定大小的（通常是这样的），也可以是可变大小的（例如存储在 Web 服务器上的远程 HTML 文件）。
>
> 类似地，第 k 层的存储器被划分成较少的块的集合，每个块的大小于 k+1 层的块的大小一样。在任何时刻，第 k 层的缓存包含第 k+1 层块的一个子集的副本。
>
> 数据总是以块大小为传送单元（transfer unit）在第 k 层和第 k+1 层之间来回复制的。虽然在层次结构中任何相邻的层次之间块大小是固定的，但是其他的层次对之间可以有不同的块大小。一般而言，层次结构中较低层（离 CPU较远）的设备的访问时间较长，因此为了补偿这些较长的访问时间，倾向于使用较大的块。
>
> 1. 缓存命中
>
>    当程序需要第 k+1 层的某个数据对象 d 时，它首先在当前存储在第 k 层的一个块中查找 d。如果 d 刚好缓存在第 k 层中，那么就是我们所说的缓存命中（cache hit）。
>
> 2. 缓存不命中
>
>    另一方面，如果第 k 层中没有缓存数据对象 d，那么就是我们所说的缓存不命中（cache miss）。当发生缓存不命中时，第 k 层的缓存从 k+1 层缓存中取出包含 d 的那个快，如果第 k 层的缓存已经满了，可能就会覆盖现存的一个块。
>
>    覆盖一个现存的块的过程称为替换（replacing）或驱逐（evicting）这个块。被驱逐的这个块有时也称为牺牲块（victim block）。决定该替换哪个块是由缓存的替换策略（replacement policy）来控制的。例如，一个具有随机替换策略的缓存会随机选择一个牺牲块。一个具有最近最少被使用（LRU）替换策略的缓存会选择那个最后被访问的时间距现在最远的块。
>
> 3. 缓存不命中的种类
>
>    如果第 k 层的缓存是空的，那么对任何数据对象的访问都会不命中。一个空的缓存有时被称为冷缓存（cold cache），此类不命中称为强制性不命中（compulsory miss）或冷不命中（cold miss）。冷不命中很重要，因为它们通常是短暂的时间，不会在反复访问存储器使得缓存暖身（warmed up）之后的稳定状态中出现。
>
>    只要发生了不命中，第 k 层的缓存就必须执行某个放置策略（placement policy），确定把它从第 k+1 层中取出的块放在那里。对于存储器层次结构中高层的缓存（靠近 CPU），它们是用硬件来实现的，而且速度是最优的，这个策略实现起来通常很昂贵，因为随机地放置块，定位起来代价很高。
>
>    因此，硬件缓存通常使用的是更严格的放置策略，这个策略将第 k+1 层的某个块限制放置在第 k 层块的一个小的子集中（有时只是一个块）。
>
>    这种限制性的放置策略会引起一种不命中，称为冲突不命中（conflict miss），在这种情况中，缓存足够大，能够保证被引用的数据对象，但是因为这些对象会映射到同一个缓存块，缓存会一直不命中。
>
>    程序通常是按照一系列阶段（如循环）来运行的，每个阶段访问缓存块的某个相对稳定不变的集合。例如，一个嵌套的循环可能会反复地访问同一个数组的元素。这个块的集合称为这个阶段的工作集（working set）。当工作集的大小超过缓存的大小时，缓存会经历容量不命中（capacity miss）。换句话说就是，缓存太小了，不能处理这个工作集。
>
> 4. 缓存管理
>
>    这里，我们的意思是指某个东西要将缓存划分成块，在不同的层之间传送块，判定是命中还是不命中，并处理它们。管理缓存的逻辑可以是硬件、软件，或是两者的结合。
>
>    例如，编译器管理寄存器文件，缓存层次结构的最高层。它决定当发生不命中时何时发射加载，以及确定哪个寄存器来存放数据。L1、L2 和 L3 层的缓存完全是由内置在缓存中的硬件逻辑来管理的。在一个有虚拟内存的系统中，DRAM 主存作为存储在磁盘上的数据块的缓存，是由操作系统软件和 CPU 上的地址翻译硬件共同管理的。

#### 6.3.2 存储器层次结构概念小节

> 概括来说，基于缓存的存储器层次结构行之有效，是因为较慢的存储设备比较快的存储设备更便宜，还因为程序倾向于展示局部性：
>
> - 利用时间局部性：由于时间局部性，同一数据对象可能会被多次使用。一旦一个数据对象在第一次不命中时复制到缓存中，我们就会期望后面对该目标有一系列的访问命中。
> - 利用空间局部性：块通常包含有多个数据对象。由于空间局部性，我们会期望后面对该块中其他对象的访问能够补偿不命中后复制该块的花费。

### 6.4 高速缓存存储器

> 我们会假设一个简单的存储器层次结构，CPU 和主存之间只有 L1 高速缓存。

#### 6.4.1 通用的高速缓存存储器组织结构

> 一般而言，高速缓存的结构可以用元组（S，E，B，m）来描述。高速缓存的大小（或容量）C 指的是所有块的大小的和。标记位和有效位不包括在内。因此，C = S\*E\*B。
>
> 参数 S 和 B 将 m 个地址分为了三个字段。A 中 s 个组索引位是一个到 S 个组的数组的索引。组索引为被解释为一个无符号整数，A 中的 t 个标记位就告诉我们这个组中的哪一行包含这个字（如果有的话）。当且仅当设置了有效位并且该行的标记位与地址 A 中的标记位相匹配时，组中的这个一行才包含这个字。一旦我们在由组索引标识的组中定位了由标号所标识的行，那么 b 个块偏移位给出了在 B 个字节的数据块中的字偏移。

`S` 高速缓存被组织成的数组个数；

`E` 每个组包含的高速缓存行（cache line）数量；

`B` 每一行高速缓存行包含的字节；

`C` 高速缓存的大小（或容量）；

`t` 每一行高速缓存行包含的标记位位数；地址中同样的位数的内容作为与高速缓存标记位匹配；

`m` 地址空间所占的位数；

`s` 高速缓存数组个数所需要的位数，用作索引；

`b` 每一行高速缓存行包含的字节个数所需要的位数，用作索引；

一个 `m` 位的地址 `A`，被分割成 `t`、`s`、`b` 部分；

#### 6.4.2 直接映射高速缓存

> 每个组只有一行（E = 1）的高速缓存称为直接映射高速缓存（direct-mapped cache）。
>
> 高速缓存确定一个请求是否命中，然后抽取出被请求的字的过程，分为三步：1）组选择；2）行匹配；3）字抽取。
>
> 1. 直接映射高速缓存中的组选择
>
>    在这一步中，高速缓存从 w 的地址中间抽取出 s 个组索引位。这些位被解释成一个对应于一个组号的无符号整数。
>
> 2. 直接映射高速缓存中的行匹配
>
>    当且仅当设置了有效位，而且高速缓存行中的标记与 w 的地址中的标记相匹配时，这一行中包含 w 的一个副本。
>
> 3. 直接映射高速缓存中的字的选择
>
>    块偏移位提供了所需要的字的第一个字节的偏移。
>
> 4. 直接映射高速缓存中不命中时的行替换
>
>    如果缓存不命中，那么它需要从存储器层次结构中的下一层取出被请求的块，然后将新的块存储在组索引位指示的组中的一个高速缓存行中。
>
> 5. 综合：运行中的直接映射高速缓存
>
> 6. 直接映射高速缓存中的冲突不命中
>
>    当程序访问大小为 2 的幂的数组时，直接映射高速缓存中通常会发生冲突不命中。
>    
>    术语“抖动（thrash）”描述的是这样一种情况，即高速缓存反复地加载和驱逐相同地高速缓存块地组。
>    
>    简单来说就是，即使程序有良好地空间局部性，而且我们的高速缓存中也有足够的空间来存放块，每次引用还是会导致冲突不命中，这是因为这些块被映射到了同一个高速缓存组。
>    
>    一旦程序员意识到了正在发生什么，就很容易修正抖动问题。一个很简单的方法是在每个数组的结尾放 B 字节的填充。
>
> **为什么用中间的位来做索引**
>
> 如果高位用作索引，那么一些连续的内存块就会映射到相同的高速缓存块。如果一个程序有良好的空间局部性，顺序扫描一个数组的元素，那么在任何时刻，高速缓存都保存着一个块大小的数组内容。这样对高速缓存的使用效率很低。相比较而言，以中间位作为索引，相邻的块总是映射到不同的高速缓存行。在这里的情况中，高速缓存能够存放整个大小为 C 的数组片，这里 C 是高速缓存的大小。

#### 6.4.3 组相联高速缓存

> 组相联高速缓存（set associative cache）每个组都保存有多于一个的高速缓存行。一个 1<E<C/B 的高速缓存通常称为 E 路组相联高速缓存。
>
> 1. 组相联高速缓存中的组选择
>
>    它的组选择与直接映射高速缓存的组选择一样，组索引位标识组。
>
> 2. 组相联高速缓存中的行匹配和字选择
>
>    组相联高速缓存必须检查多个行的标记位和有效位，以确定所请求的字是否在集合中。传统的内存是一个值得数组，以地址作为输入，并返回存储在那个地址得值。另一方面，相联存储器是一个（key，value）对得数组，以 key 为输入，返回与输入的 key 相匹配的（key，value）对中的 value 值。因此，我们可以把组相联高速缓存中的每个组都看成一个小的相联存储器，key 是标记和有效位，而 value 就是块的内容。
>
>    组中的任何一行都可以包含任何映射到这个组的内存块。所以高速缓存必须搜索组中的每一行，寻找一个有效的行，其标记与地址中的标记相匹配。如果高速缓存找到了这样一行，那么我们就命中，块偏移从这个块中选择一个字，和前面一样。
>
> 3. 组相联高速缓存中不命中时的行替换
>
>    程序员很难在代码中利用高速缓存替换策略。最简单的替换策略是随机选择要替换的行。其他更复杂的策略利用了局部性原理，以使在比较近的将来引用被替换的行的概率最小。例如，最不常使用（Least-Frequently-Used，LFU）策略会替换在过去某个时间窗口内引用次数最少的那一行。最近最少使用（Least-Recently-Used，LRU）策略会替换最后一次访问时间最久远的那一行。所有这些策略都需要额外的时间和硬件。但是越往存储器层次结构下面走，远离 CPU，一次不命中的开销就会更加昂贵，用更好的替换策略使得不命中最少也变得更加值得了。

#### 6.4.4 全相联高速缓存

> 全相联高速缓存（fully associative cache）是由一个包含所有高速缓存行的组（即 E=C/B）组成的。
>
> 1. 全相联高速缓存中的组选择
>
>    全相联高速缓存中的组选择非常简单，因为只有一个组。注意地址中没有组索引位，地址只被划分成了一个标记和一个块偏移。
>
> 2. 全相联高速缓存中的行匹配和字选择
>
>    全相联高速缓存中的行匹配和字选择与组相联高速缓存中的是一样的。它们之间的区别主要是规模大小的问题。
>
>    因为高速缓存电路必须并行地搜索许多相匹配的标记，构造一个又大又快的相联高速缓存很困难，而且很昂贵。因此，全相联高速缓存只适合做小的高速缓存，例如虚拟内存系统中的翻译备用缓冲器（TLB），它缓存页表项。

#### 6.4.5 有关写的问题

> 写的情况就要复杂一些了。假设我们要写一个已经缓存了的字 w（写命中，write hit）。最简单的方法，称为直写（write-through），就是立即将 w 的高速缓存块写回到紧接着的第一层中。虽然简单，但是直写的缺点是每次都会引起总线流量。另一种方法，称为写回（write-back），尽可能地推迟更新，只有当替换算法要驱逐这个更新过的块时，才把它写到紧接着的低一层中。由于局部性，写回能显著地减少总线流量，但是它的缺点是增加了复杂性。高速缓存必须为每个高速缓存行维护一个额外的修改位（dirty bit），表明这个高速缓存块是否被修改过。
>
> 另一个问题是如何处理写不命中。一种方法，称为写分配（write-allocate），加载相应的低一层的块到高速缓存中，然后更新这个高速缓存块。写分配试图利用写的空间局部性，但是缺点是每次不命中都会导致一个块从低一层传送到高速缓存。另一种方法，称为非写分配（not-write-allocate），避开高速缓存，直接把这个字写到低一层中。直写高速缓存通常是非写分配的。写回高速缓存通常是写分配的。
>
> 对于试图编写高速缓存比较友好的程序的程序员来说，我们建议在心里采用一个使用写回和写分配的高速缓存的模型。通常，由于较长的传送时间，存储器层次结构中较低层的缓存更可能使用写回，而不是直写。例如，虚拟内存系统（用主存作为存储在磁盘上的块的缓存）只使用写回。但是由于逻辑电路密度的提高，写回的搞复杂性也越不成为阻碍了，我们在现代系统的所有层次上都能看到写回缓存。所以这种假设符合当前的趋势。假设使用写回写分配的另一个原因是，它与处理读的方式相对称，因为写回写分配试图利用局部性。因此，我们可以在高层次上开发我们的程序，展示良好的空间和时间局部性，而不是试图为某一个存储器进行优化。

#### 6.4.6 一个真实的高速缓存层次结构的解剖

> 到目前为止，我们一直假设高速缓存只保存程序数据。不过，实际上，高速缓存既保存数据，也保存指令。只保存指令的高速缓存称为 i-cache。只保存程序数据的高速缓存称为 d-cache。既保存指令又包括数据的高速缓存称为统一的高速缓存（unified cache）。现代处理器包括独立的 i-cache 和 d-cache。有两个独立的高速缓存，处理器能够同时读一个指令字和一个数据字。i-cache 通常是只读的，因此比较简单。通常会针对不同的访问模式来优化这两个高速缓存，它们可以有不同的块大小，相联度和容量。使用不同的高速缓存也确保了数据访问不会与指令访问形成冲突不命中，反过来也是一样，代价就是可能会引起容量不命中增加。

#### 6.4.7 高速缓存参数的性能影响

> 有许多指标来衡量高速缓存的性能：
>
> - 不命中率（miss rate）。在一个程序执行或程序的一部分执行期间，内存引用不命中的比率。它是这样计算的：不命中数量/引用数量。
> - 命中率（hit rate）。命中的内存引用比率。它等于 1-不命中率。
> - 命中时间（hit time）。从高速缓存传送一个字到 CPU 所需的时间，包括组选择、行确认和字选择的时间。对于 L1 高速缓存来说，命中时间的数量级是几个时钟周期。
> - 不命中处罚（miss penalty）。由于不命中所需要的额外的时间。L1 不命中需要从 L2 得到服务的处罚，通常是数 10 个周期；从 L3 得到服务的处罚，50个周期；从主存得到的服务的处罚，200 个周期。
>
> 1. 高速缓存大小的影响
>
>    一方面，较大的高速缓存可能会提高命中率。另一方面，使大存储器运行得更快总是要难一些的。结果，较大的高速缓存会增加命中时间。
>
> 2. 块大小的影响
>
>    大的块有利有弊。一方面，较大的块利用程序中可能存在的空间局部性，帮助提高命中率。不过，对于给定的高速缓存大小，块越大就意味着高速缓存行数越少，这会损害时间局部性比空间局部性更好的程序中的命中率。较大的块对不命中处罚也有负面影响，因为块越大，传送时间就越长。现代系统（如 Core i7）会折中使高速缓存块包含 64 个字节。
>
> 3. 相联度的影响
>
>    这里的问题是参数 E 选择的影响，E 是每个组中高速缓存行数。较高的相联度（也就是 E 的值较大）的优点是降低了高速缓存由于冲突不命中出现抖动的可能性。不过，较高的相联度会造成较高的成本。较高的相联度实现起来很昂贵，而且很难使之速度变快。每一行需要更多的标记位，每一行需要额外的 LRU 状态位和额外的控制逻辑。较高的相联度会增加命中时间，因为复杂性增加了，另外，还会增加不命中处罚，因为选择牺牲行的复杂性也增加了。
>
> 4. 写策略的影响
>
>    直写高速缓存比较容易实现，而且能使用独立于高速缓存的写缓冲区（write buffer），用来更新内存。此外，读不命中开销没那么大，因为它们不会触发内存写。另一方面，写回高速缓存引起的传送比较少，它允许更多的到内存的带宽用于执行 DMA 的 I/O 设备。此外，越往层次结构下面走，传送时间增加，减少传送的数量就变得更加重要。一般而言，高速缓存越往下层，越可能使用写回而不是直写。

多核 CPU 的情况下有多个一级缓存，如果保证缓存内部数据的一致，不让系统数据混乱。这里就引出了一个一致性的协议 MESI。

MESI 是指 4 种状态的首字母。每个缓存行有 4 种状态，可用 2 个位表示，它们分别是：

- M 修改（Modified）

  该缓存行有效，数据被修改了，和内存的数据不一致，数据只存在于本缓存中。

- E 独享、互斥（Exclusive）

  该缓存行有效，数据和内存中的数据一致，数据只存在于本缓存中。

- S 共享（Shared）

  该缓存行有效，数据和内存中的数据一致，数据存在于很多缓存中。

- I 无效（Invalid）

  该缓存行无效。

### 6.5 编写高速缓存友好的代码

> 局部性比较好的程序更容易有较低的不命中率，而不命中率较低的程序往往比不命中率较高的程序运行得更快。好的程序员总是应该去编写高速缓存友好（cache friendly）的代码。下面就是我们用来确保代码高速缓存友好的基本方法。
>
> 1. 让最常见的情况运行得快。程序通常把大部分时间花在少量的核心函数上，而这些函数通常把大部分时间都花在了少量循环上。所以要把注意力集中在核心函数里的循环上，而忽略其他部分。
> 2. 尽量减少每个循环内部的缓存不命中数量。在其他条件（例如加载和存储的总次数）相同的情况下，不命中较低的循环运行得更快。
>
> 任何合理的优化编译器都会把局部变量缓存在寄存器文件中，也就是存储器层次结构的最高层中。一般而言，如果一个高速缓存的块大小为 B 字节，那么一个步长为 k 的引用模式（这里 k 是以字为单位的）平均每次循环迭代会有 min(1, (wordsize*k)/B) 次缓存不命中。
>
> 两个关于编写高速缓存友好的代码的重要问题：
>
> - 对局部变量的反复引用是好的，因为编译器能够将它们缓存在寄存器文件中（时间局部性）。
> - 步长为 1 的引用模式是好的，因为存储器层次结构中所有层次上的缓存都是将数据存储为连续的块（空间局部性）。
>
> 在对多维数组进行操作的程序中，空间局部性尤其重要。
>
> 总之，程序员应该注意他们程序中的局部性，试着编写利用局部性的程序。

### 6.6 综合：高速缓存对程序性能的影响

#### 6.6.1 存储器山

> 一个程序从存储系统中读数据的速率称为读吞吐量（read throughput），或者有时称为读带宽（read bandwidth）。如果一个程序在 s 秒的时间内读 n 个字节，那么这段时间内的读吞吐量就等于 n/s，通常以兆字节每秒（MB/s）为单位。
>
> run 函数的参数 size 和 stride 允许我们控制产出的读序列的时间和空间局部性程度。size 的值越小，得到的工作集越小，因此时间局部性越好。stride  的值越小，得到的空间局部性越好。如果我们反复以不同的 size 和 stride 值调用 run 函数，那么我们就能得到一个读带宽的时间和空间局部性的二维函数，称为存储器山（memory mountain）。
>
> 即使当工作集太大，不能全部装进任何一个高速缓存时，主存山脊的最高点也比它的最低点高 8 倍。因此，即使是当程序的时间局部性很差时，空间局部性仍然能补救，并且是非常重要的。
>
> 对于步长 1 垂直于步长轴，此时读吞吐量相对保持不变，为 12 GB/s，即使工作集超出了 L1 和 L2 的大小。这显然是由于 Core i7 存储器系统中的硬件预取（prefetching）机制，它会自动地识别顺序的、步长为 1 的引用模式，试图在一些块被访问之前，将它们取到高速缓存中。这也是代码中要使用步长为 1 的顺序访问的另一个理由。
>
> 工作集大小固定为 4MB 时的片段。这个片段沿着 L3 山脊切的，这里，工作集完全能够放到 L3 高速缓存中，但是对 L2 高速缓存来说太大了。一旦步长达到了 8 个字，在这个系统上就等于块的大小 64 个字节了，每个读请求在 L2 中都会不命中，必须从 L3 服务。因此，对于至少为 8 个字的步长来说，读吞吐量是一个常数速率，是由从 L3 传送高速缓存块到 L2 的速率决定的。
>
> 总结一下我们对存储器山的讨论，存储器系统的性能不是一个数字就能描述的。相反，它是一座时间和空间局部性的山，这座山的上升高度差别可以超过一个数量级。明智的程序员会试图构造他们的程序，使得程序运行在山峰而不是低估。目标就是利用时间局部性，使得频繁使用的字从 L1 中取出，还要利用空间局部性，使得尽可能多的字从一个 L1 高速缓存行中访问到。

#### 6.6.2 重新排列循环以提高空间局部性

> 与内存访问总数相比，不命中率是一个更好的性能预测指标。
>
> 对于大的 n 值（数组大小），最快的版本的性能保持不变。虽然这个数组远大于任何 SRAM 高速缓存存储器，但预取硬件足够聪明，能够认出步长为 1 的访问模式，而且速度足够快能够跟上内循环中的内存访问。这是设计这个内存系统的 Intel 的工程师所做的一项极好成就，像程序员提供了甚至更多的鼓励，鼓励他们开发出具有良好空间局部性的程序。
>
> **使用分块来提高时间局部性**
>
> 分块（blocking）可以提高内循环的时间局部性。分块的大致思想是将一个程序中的数据结构组织成大的片（chunk），称为（block）。（在这个上下文中，“块”指的是一个应用级的数据组块，而不是告诉缓存块）。这样结构程序，使得能够一个片加载到 L1 高速缓存中，并在这个片中进行所需的所有的读和写，然后丢掉这个片，加载下一个片，以此类推。
>
> 与为提高空间局部性所做的简单循环变换不同，分块使得代码更难阅读和理解。由于这个原因，它最适合于优化编译器或者频繁执行的库函数。由于 Core i7  有完善的预取硬件，分块不会提高矩阵乘在 Core i7 上的性能。不过，学习和理解这项技术还是很有趣的，因为它是一个通用的概念，可以在一些没有预取的系统上获得极大的性能收益。

在复杂度相同时，在空间局部性上还能再优化。

#### 6.6.3 在程序中利用局部性

> 有良好局部性的程序从快速的高速缓存存储器中访问它的大部分数据。局部性差的程序从相对慢速的 DRAM 主存中访问它的大部分数据。
>
> 推荐下列技术：
>
> - 将注意力集中在内循环上，大部分计算和内存访问都发生在这里。
> - 通过按照数据对象存储在内存中的顺序，以步长为 1 的来读数据，从而使得程序中的空间局部性最大。
> - 一旦从存储器中读入了一个数据对象，就尽可能多地使用它，从而使得程序中的时间局部性最大。

### 6.7 小结

> 系统通过将存储器组织成存储设备的层次结构来弥补这些差异，在这个层次结构中，较小、较快的设备在顶部，较大、较慢的设备在底部。因为编写良好的程序有好的局部性，大多数数据都可以从较高层得到服务，结果就是存储系统能以较高层的速度运行，但却有较低层的成本和容量。


