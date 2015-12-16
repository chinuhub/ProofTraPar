# 1 "../../Examples/ThreaderFormat/time_var_mutex.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "../../Examples/ThreaderFormat/time_var_mutex.c"
int block;
int busy;
int inode;
int m_inode=0;
int m_busy=0;

thr1(){
  glb_init(inode == busy);
  acquire(m_inode);
  if(inode == 0){
    acquire(m_busy);
    busy = 1;
    release(m_busy);
    inode = 1;
  }
  block = 1;
  assert(block == 1);
  release(m_inode);
}

thr2(){
  acquire(m_busy);
  if(busy == 0){
    block = 0;
    assert(block == 0);
  }
  release(m_busy);
}
