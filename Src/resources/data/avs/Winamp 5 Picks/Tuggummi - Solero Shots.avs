Nullsoft AVS Preset 0.2    �  �  Solero Shots
____________________________________________

WinAmp 5 edit
- Turned off bilinear filtering from one movement. Slightly better fps.

Original preset from "Breaking Myself"

____________________________________________
All code written by Jukka Keskinarkaus (aka Tuggummi)
Feel free to modify or use parts of this preset to make your own  presets, but don't copy the whole preset and claim you did that  preset. ����5'  �   $�   �                                   ����   ����   ��������+        x1=x ; y1=y ;
x=x+sxt+sin(y1*ym1+cos(x*xm2+xt3)+xt3)*str ;
y=y+syt+sin(x1*ym1+cos(y*xm2+yt3)+yt3)*str ;
d=sqrt(sqr(x)+sqr(y)) ; r=atan2(x,y) ;
d1=d ; r1=r ;
d=d*zoom+sin(d1*dm+dt)*str*0.5 ; r=r+sin(d1*rm*3+rt)*str+rot ;
x=sin(r)*d-sxt ; y=cos(r)*d-syt ;
alpha=0.9 �  p=p*0.9 ;
spd=getspec(0.01,0.02,0)*0.003 ;
xt=xt+xts ; xt2=xt2+xts2 ; xt3=xt3+xts3 ;
yt=yt+yts ; yt2=yt2+yts2 ; yt3=yt3+yts3 ;
dt=dt+dts ; dt2=dt2+dts2 ;
rt=rt+rts ; rt2=rt2+rts2 ;
xm1=1.5+abs(sin(xt*0.333))*2 ; xm2=1+abs(sin(xt2)) ;
ym1=1.5+abs(sin(yt*0.333))*2 ; ym2=1+abs(sin(yt2)) ;
dm=3+abs(sin(dt2)) ;
str=0.02+p ;
rm=1+abs(sin(rt2*0.5)) ;
rot=sin(rt)*0.02 ;
zoom=1-p*0.2 ;
sxt=sin((xt3+xt)*0.5)*0.1 ;
syt=sin((yt3+yt)*0.5)*0.1    xts=(rand(101)-50)*spd ; xts2=(rand(101)-50)*spd ; xts3=(rand(101)-50)*spd ;
yts=(rand(101)-50)*spd ; yts2=(rand(101)-50)*spd ; yts3=(rand(101)-50)*spd ;
dts=(rand(101)-50)*spd ; dts2=(rand(101)-50)*spd ;
rts=(rand(101)-50)*spd ; rts2=(rand(101)-50)*spd ;
p=getspec(0.02,0.03,0)*0.15                               �����"  � $�   �                          $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���     $   N     x=xt ;
y=yt �   clr=rand(3) ; xts=((rand(15)-7)/w) ; yts=((rand(15)-7)/w) ; xt=if(above(xt,0.4),-0.4,if(below(xt,-0.4),0.4,xt+xts)) ; yt=if(above(yt,0.4),-0.4,if(below(yt,-0.4),0.4,yt+yts)) ; red=equal(clr,0) ; green=equal(clr,1) ; blue=equal(clr,2)     6   n=1 ; xt=(rand(81)-40)*0.01 ; yt=(rand(81)-40)*0.01 ;       ���        %   �     d=d*0.4                     l�LHolden03: Convolution Filter    �                                                                                                                                                                                                                     ,             1   �     d=d*1.1-sqr(d)*0.35                    �q�Color Map                       �                     �C�                                                         �                                                         ?�                                                        �H�                                                        �H�                                                        G�                                                        �F�                                                        �@�                                                             �   �l                 �   ���                �   ���                �   ���                �   ���                �   ���                �   ���                �   ���       (             �  c  g                %         