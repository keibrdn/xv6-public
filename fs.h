#define ROOTINO 1  
#define BSIZE 512  


struct superblock {
  uint size;         
  uint nblocks;      
  uint ninodes;      
  uint nlog;         
  uint logstart;     
  uint inodestart;  
  uint bmapstart;    
};

#define NDIRECT 12
#define NINDIRECT (BSIZE / sizeof(uint))
#define MAXFILE (NDIRECT + NINDIRECT)

struct dinode {
  short type;           
  short major;          
  short minor;          
  short nlink;         
  uint size;            
  uint addrs[NDIRECT+1];   
};

#define IPB           (BSIZE / sizeof(struct dinode))

#define IBLOCK(i, sb)     ((i) / IPB + sb.inodestart)

#define BPB           (BSIZE*8)

#define BBLOCK(b, sb) (b/BPB + sb.bmapstart)

#define DIRSIZ 14

struct dirent {
  ushort inum;
  char name[DIRSIZ];
};

