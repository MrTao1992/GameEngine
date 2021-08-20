# NOTE: Assertions have been autogenerated by utils/update_mca_test_checks.py
# RUN: llvm-mca -mtriple=x86_64-unknown-unknown -mcpu=x86-64 -instruction-tables < %s | FileCheck %s

emms

movd        %eax, %mm2
movd        (%rax), %mm2

movd        %mm0, %ecx
movd        %mm0, (%rax)

movq        %rax, %mm2
movq        (%rax), %mm2

movq        %mm0, %rcx
movq        %mm0, (%rax)

packsswb    %mm0, %mm2
packsswb    (%rax), %mm2

packssdw    %mm0, %mm2
packssdw    (%rax), %mm2

packuswb    %mm0, %mm2
packuswb    (%rax), %mm2

paddb       %mm0, %mm2
paddb       (%rax), %mm2

paddd       %mm0, %mm2
paddd       (%rax), %mm2

paddsb      %mm0, %mm2
paddsb      (%rax), %mm2

paddsw      %mm0, %mm2
paddsw      (%rax), %mm2

paddusb     %mm0, %mm2
paddusb     (%rax), %mm2

paddusw     %mm0, %mm2
paddusw     (%rax), %mm2

paddw       %mm0, %mm2
paddw       (%rax), %mm2

pand        %mm0, %mm2
pand        (%rax), %mm2

pandn       %mm0, %mm2
pandn       (%rax), %mm2

pcmpeqb     %mm0, %mm2
pcmpeqb     (%rax), %mm2

pcmpeqd     %mm0, %mm2
pcmpeqd     (%rax), %mm2

pcmpeqw     %mm0, %mm2
pcmpeqw     (%rax), %mm2

pcmpgtb     %mm0, %mm2
pcmpgtb     (%rax), %mm2

pcmpgtd     %mm0, %mm2
pcmpgtd     (%rax), %mm2

pcmpgtw     %mm0, %mm2
pcmpgtw     (%rax), %mm2

pmaddwd     %mm0, %mm2
pmaddwd     (%rax), %mm2

pmulhw      %mm0, %mm2
pmulhw      (%rax), %mm2

pmullw      %mm0, %mm2
pmullw      (%rax), %mm2

por         %mm0, %mm2
por         (%rax), %mm2

pslld       $1, %mm2
pslld       %mm0, %mm2
pslld       (%rax), %mm2

psllq       $1, %mm2
psllq       %mm0, %mm2
psllq       (%rax), %mm2

psllw       $1, %mm2
psllw       %mm0, %mm2
psllw       (%rax), %mm2

psrad       $1, %mm2
psrad       %mm0, %mm2
psrad       (%rax), %mm2

psraw       $1, %mm2
psraw       %mm0, %mm2
psraw       (%rax), %mm2

psrld       $1, %mm2
psrld       %mm0, %mm2
psrld       (%rax), %mm2

psrlq       $1, %mm2
psrlq       %mm0, %mm2
psrlq       (%rax), %mm2

psrlw       $1, %mm2
psrlw       %mm0, %mm2
psrlw       (%rax), %mm2

psubb       %mm0, %mm2
psubb       (%rax), %mm2

psubd       %mm0, %mm2
psubd       (%rax), %mm2

psubsb      %mm0, %mm2
psubsb      (%rax), %mm2

psubsw      %mm0, %mm2
psubsw      (%rax), %mm2

psubusb     %mm0, %mm2
psubusb     (%rax), %mm2

psubusw     %mm0, %mm2
psubusw     (%rax), %mm2

psubw       %mm0, %mm2
psubw       (%rax), %mm2

punpckhbw   %mm0, %mm2
punpckhbw   (%rax), %mm2

punpckhdq   %mm0, %mm2
punpckhdq   (%rax), %mm2

punpckhwd   %mm0, %mm2
punpckhwd   (%rax), %mm2

punpcklbw   %mm0, %mm2
punpcklbw   (%rax), %mm2

punpckldq   %mm0, %mm2
punpckldq   (%rax), %mm2

punpcklwd   %mm0, %mm2
punpcklwd   (%rax), %mm2

pxor        %mm0, %mm2
pxor        (%rax), %mm2

# CHECK:      Instruction Info:
# CHECK-NEXT: [1]: #uOps
# CHECK-NEXT: [2]: Latency
# CHECK-NEXT: [3]: RThroughput
# CHECK-NEXT: [4]: MayLoad
# CHECK-NEXT: [5]: MayStore
# CHECK-NEXT: [6]: HasSideEffects (U)

# CHECK:      [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
# CHECK-NEXT:  31     31    10.33   *      *      U     emms
# CHECK-NEXT:  1      1     1.00                        movd	%eax, %mm2
# CHECK-NEXT:  1      5     0.50    *                   movd	(%rax), %mm2
# CHECK-NEXT:  1      2     1.00                        movd	%mm0, %ecx
# CHECK-NEXT:  1      1     1.00           *      U     movd	%mm0, (%rax)
# CHECK-NEXT:  1      1     1.00                        movq	%rax, %mm2
# CHECK-NEXT:  1      5     0.50    *                   movq	(%rax), %mm2
# CHECK-NEXT:  1      2     1.00                        movq	%mm0, %rcx
# CHECK-NEXT:  1      1     1.00           *            movq	%mm0, (%rax)
# CHECK-NEXT:  1      1     1.00                        packsswb	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   packsswb	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        packssdw	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   packssdw	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        packuswb	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   packuswb	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        paddb	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   paddb	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        paddd	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   paddd	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        paddsb	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   paddsb	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        paddsw	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   paddsw	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        paddusb	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   paddusb	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        paddusw	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   paddusw	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        paddw	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   paddw	(%rax), %mm2
# CHECK-NEXT:  1      1     0.33                        pand	%mm0, %mm2
# CHECK-NEXT:  2      6     0.50    *                   pand	(%rax), %mm2
# CHECK-NEXT:  1      1     0.33                        pandn	%mm0, %mm2
# CHECK-NEXT:  2      6     0.50    *                   pandn	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        pcmpeqb	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   pcmpeqb	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        pcmpeqd	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   pcmpeqd	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        pcmpeqw	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   pcmpeqw	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        pcmpgtb	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   pcmpgtb	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        pcmpgtd	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   pcmpgtd	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        pcmpgtw	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   pcmpgtw	(%rax), %mm2
# CHECK-NEXT:  1      5     1.00                        pmaddwd	%mm0, %mm2
# CHECK-NEXT:  2      10    1.00    *                   pmaddwd	(%rax), %mm2
# CHECK-NEXT:  1      5     1.00                        pmulhw	%mm0, %mm2
# CHECK-NEXT:  2      10    1.00    *                   pmulhw	(%rax), %mm2
# CHECK-NEXT:  1      5     1.00                        pmullw	%mm0, %mm2
# CHECK-NEXT:  2      10    1.00    *                   pmullw	(%rax), %mm2
# CHECK-NEXT:  1      1     0.33                        por	%mm0, %mm2
# CHECK-NEXT:  2      6     0.50    *                   por	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        pslld	$1, %mm2
# CHECK-NEXT:  1      1     1.00                        pslld	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   pslld	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        psllq	$1, %mm2
# CHECK-NEXT:  1      1     1.00                        psllq	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   psllq	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        psllw	$1, %mm2
# CHECK-NEXT:  1      1     1.00                        psllw	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   psllw	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        psrad	$1, %mm2
# CHECK-NEXT:  1      1     1.00                        psrad	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   psrad	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        psraw	$1, %mm2
# CHECK-NEXT:  1      1     1.00                        psraw	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   psraw	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        psrld	$1, %mm2
# CHECK-NEXT:  1      1     1.00                        psrld	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   psrld	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        psrlq	$1, %mm2
# CHECK-NEXT:  1      1     1.00                        psrlq	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   psrlq	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        psrlw	$1, %mm2
# CHECK-NEXT:  1      1     1.00                        psrlw	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   psrlw	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        psubb	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   psubb	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        psubd	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   psubd	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        psubsb	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   psubsb	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        psubsw	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   psubsw	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        psubusb	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   psubusb	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        psubusw	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   psubusw	(%rax), %mm2
# CHECK-NEXT:  1      3     1.00                        psubw	%mm0, %mm2
# CHECK-NEXT:  2      8     1.00    *                   psubw	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        punpckhbw	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   punpckhbw	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        punpckhdq	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   punpckhdq	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        punpckhwd	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   punpckhwd	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        punpcklbw	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   punpcklbw	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        punpckldq	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   punpckldq	(%rax), %mm2
# CHECK-NEXT:  1      1     1.00                        punpcklwd	%mm0, %mm2
# CHECK-NEXT:  2      6     1.00    *                   punpcklwd	(%rax), %mm2
# CHECK-NEXT:  1      1     0.33                        pxor	%mm0, %mm2
# CHECK-NEXT:  2      6     0.50    *                   pxor	(%rax), %mm2

# CHECK:      Resources:
# CHECK-NEXT: [0]   - SBDivider
# CHECK-NEXT: [1]   - SBFPDivider
# CHECK-NEXT: [2]   - SBPort0
# CHECK-NEXT: [3]   - SBPort1
# CHECK-NEXT: [4]   - SBPort4
# CHECK-NEXT: [5]   - SBPort5
# CHECK-NEXT: [6.0] - SBPort23
# CHECK-NEXT: [6.1] - SBPort23

# CHECK:      Resource pressure per iteration:
# CHECK-NEXT: [0]    [1]    [2]    [3]    [4]    [5]    [6.0]  [6.1]
# CHECK-NEXT:  -      -     21.00  53.00  2.00   57.00  24.00  24.00

# CHECK:      Resource pressure by instruction:
# CHECK-NEXT: [0]    [1]    [2]    [3]    [4]    [5]    [6.0]  [6.1]  Instructions:
# CHECK-NEXT:  -      -     10.33  10.33   -     10.33   -      -     emms
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     movd	%eax, %mm2
# CHECK-NEXT:  -      -      -      -      -      -     0.50   0.50   movd	(%rax), %mm2
# CHECK-NEXT:  -      -     1.00    -      -      -      -      -     movd	%mm0, %ecx
# CHECK-NEXT:  -      -      -      -     1.00    -     0.50   0.50   movd	%mm0, (%rax)
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     movq	%rax, %mm2
# CHECK-NEXT:  -      -      -      -      -      -     0.50   0.50   movq	(%rax), %mm2
# CHECK-NEXT:  -      -     1.00    -      -      -      -      -     movq	%mm0, %rcx
# CHECK-NEXT:  -      -      -      -     1.00    -     0.50   0.50   movq	%mm0, (%rax)
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     packsswb	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   packsswb	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     packssdw	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   packssdw	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     packuswb	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   packuswb	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     paddb	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   paddb	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     paddd	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   paddd	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     paddsb	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   paddsb	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     paddsw	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   paddsw	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     paddusb	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   paddusb	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     paddusw	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   paddusw	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     paddw	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   paddw	(%rax), %mm2
# CHECK-NEXT:  -      -     0.33   0.33    -     0.33    -      -     pand	%mm0, %mm2
# CHECK-NEXT:  -      -     0.33   0.33    -     0.33   0.50   0.50   pand	(%rax), %mm2
# CHECK-NEXT:  -      -     0.33   0.33    -     0.33    -      -     pandn	%mm0, %mm2
# CHECK-NEXT:  -      -     0.33   0.33    -     0.33   0.50   0.50   pandn	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     pcmpeqb	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   pcmpeqb	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     pcmpeqd	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   pcmpeqd	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     pcmpeqw	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   pcmpeqw	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     pcmpgtb	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   pcmpgtb	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     pcmpgtd	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   pcmpgtd	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     pcmpgtw	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   pcmpgtw	(%rax), %mm2
# CHECK-NEXT:  -      -     1.00    -      -      -      -      -     pmaddwd	%mm0, %mm2
# CHECK-NEXT:  -      -     1.00    -      -      -     0.50   0.50   pmaddwd	(%rax), %mm2
# CHECK-NEXT:  -      -     1.00    -      -      -      -      -     pmulhw	%mm0, %mm2
# CHECK-NEXT:  -      -     1.00    -      -      -     0.50   0.50   pmulhw	(%rax), %mm2
# CHECK-NEXT:  -      -     1.00    -      -      -      -      -     pmullw	%mm0, %mm2
# CHECK-NEXT:  -      -     1.00    -      -      -     0.50   0.50   pmullw	(%rax), %mm2
# CHECK-NEXT:  -      -     0.33   0.33    -     0.33    -      -     por	%mm0, %mm2
# CHECK-NEXT:  -      -     0.33   0.33    -     0.33   0.50   0.50   por	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     pslld	$1, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     pslld	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   pslld	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psllq	$1, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psllq	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   psllq	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psllw	$1, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psllw	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   psllw	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psrad	$1, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psrad	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   psrad	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psraw	$1, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psraw	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   psraw	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psrld	$1, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psrld	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   psrld	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psrlq	$1, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psrlq	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   psrlq	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psrlw	$1, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     psrlw	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   psrlw	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     psubb	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   psubb	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     psubd	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   psubd	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     psubsb	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   psubsb	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     psubsw	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   psubsw	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     psubusb	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   psubusb	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     psubusw	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   psubusw	(%rax), %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -      -      -     psubw	%mm0, %mm2
# CHECK-NEXT:  -      -      -     1.00    -      -     0.50   0.50   psubw	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     punpckhbw	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   punpckhbw	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     punpckhdq	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   punpckhdq	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     punpckhwd	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   punpckhwd	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     punpcklbw	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   punpcklbw	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     punpckldq	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   punpckldq	(%rax), %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00    -      -     punpcklwd	%mm0, %mm2
# CHECK-NEXT:  -      -      -      -      -     1.00   0.50   0.50   punpcklwd	(%rax), %mm2
# CHECK-NEXT:  -      -     0.33   0.33    -     0.33    -      -     pxor	%mm0, %mm2
# CHECK-NEXT:  -      -     0.33   0.33    -     0.33   0.50   0.50   pxor	(%rax), %mm2
