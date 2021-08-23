; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -mtriple=x86_64-apple-macosx10.8.0 -mcpu=corei7 -basicaa -slp-vectorizer -dce -S | FileCheck %s --check-prefixes=CHECK,SSE42
; RUN: opt < %s -mtriple=x86_64-apple-macosx10.8.0 -mcpu=corei7-avx -basicaa -slp-vectorizer -dce -S | FileCheck %s --check-prefixes=CHECK,AVX

target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"

; int test_sext_4i8_to_4i32(int * restrict A, char * restrict B) {
;     A[0] = B[0];
;     A[1] = B[1];
;     A[2] = B[2];
;     A[3] = B[3];
; }

define i32 @test_sext_4i8_to_4i32(i32* noalias nocapture %A, i8* noalias nocapture %B) {
; CHECK-LABEL: @test_sext_4i8_to_4i32(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    [[TMP0:%.*]] = bitcast i8* [[B:%.*]] to <4 x i8>*
; CHECK-NEXT:    [[TMP1:%.*]] = load <4 x i8>, <4 x i8>* [[TMP0]], align 1
; CHECK-NEXT:    [[TMP2:%.*]] = sext <4 x i8> [[TMP1]] to <4 x i32>
; CHECK-NEXT:    [[TMP3:%.*]] = bitcast i32* [[A:%.*]] to <4 x i32>*
; CHECK-NEXT:    store <4 x i32> [[TMP2]], <4 x i32>* [[TMP3]], align 4
; CHECK-NEXT:    ret i32 undef
;
entry:
  %0 = load i8, i8* %B, align 1
  %conv = sext i8 %0 to i32
  store i32 %conv, i32* %A, align 4
  %arrayidx2 = getelementptr inbounds i8, i8* %B, i64 1
  %1 = load i8, i8* %arrayidx2, align 1
  %conv3 = sext i8 %1 to i32
  %arrayidx4 = getelementptr inbounds i32, i32* %A, i64 1
  store i32 %conv3, i32* %arrayidx4, align 4
  %arrayidx5 = getelementptr inbounds i8, i8* %B, i64 2
  %2 = load i8, i8* %arrayidx5, align 1
  %conv6 = sext i8 %2 to i32
  %arrayidx7 = getelementptr inbounds i32, i32* %A, i64 2
  store i32 %conv6, i32* %arrayidx7, align 4
  %arrayidx8 = getelementptr inbounds i8, i8* %B, i64 3
  %3 = load i8, i8* %arrayidx8, align 1
  %conv9 = sext i8 %3 to i32
  %arrayidx10 = getelementptr inbounds i32, i32* %A, i64 3
  store i32 %conv9, i32* %arrayidx10, align 4
  ret i32 undef
}

define i32 @test_zext_4i16_to_4i32(i32* noalias nocapture %A, i16* noalias nocapture %B) {
; CHECK-LABEL: @test_zext_4i16_to_4i32(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    [[TMP0:%.*]] = bitcast i16* [[B:%.*]] to <4 x i16>*
; CHECK-NEXT:    [[TMP1:%.*]] = load <4 x i16>, <4 x i16>* [[TMP0]], align 1
; CHECK-NEXT:    [[TMP2:%.*]] = zext <4 x i16> [[TMP1]] to <4 x i32>
; CHECK-NEXT:    [[TMP3:%.*]] = bitcast i32* [[A:%.*]] to <4 x i32>*
; CHECK-NEXT:    store <4 x i32> [[TMP2]], <4 x i32>* [[TMP3]], align 4
; CHECK-NEXT:    ret i32 undef
;
entry:
  %0 = load i16, i16* %B, align 1
  %conv = zext i16 %0 to i32
  store i32 %conv, i32* %A, align 4
  %arrayidx2 = getelementptr inbounds i16, i16* %B, i64 1
  %1 = load i16, i16* %arrayidx2, align 1
  %conv3 = zext i16 %1 to i32
  %arrayidx4 = getelementptr inbounds i32, i32* %A, i64 1
  store i32 %conv3, i32* %arrayidx4, align 4
  %arrayidx5 = getelementptr inbounds i16, i16* %B, i64 2
  %2 = load i16, i16* %arrayidx5, align 1
  %conv6 = zext i16 %2 to i32
  %arrayidx7 = getelementptr inbounds i32, i32* %A, i64 2
  store i32 %conv6, i32* %arrayidx7, align 4
  %arrayidx8 = getelementptr inbounds i16, i16* %B, i64 3
  %3 = load i16, i16* %arrayidx8, align 1
  %conv9 = zext i16 %3 to i32
  %arrayidx10 = getelementptr inbounds i32, i32* %A, i64 3
  store i32 %conv9, i32* %arrayidx10, align 4
  ret i32 undef
}

define i64 @test_sext_4i16_to_4i64(i64* noalias nocapture %A, i16* noalias nocapture %B) {
; SSE42-LABEL: @test_sext_4i16_to_4i64(
; SSE42-NEXT:  entry:
; SSE42-NEXT:    [[TMP0:%.*]] = bitcast i16* [[B:%.*]] to <2 x i16>*
; SSE42-NEXT:    [[TMP1:%.*]] = load <2 x i16>, <2 x i16>* [[TMP0]], align 1
; SSE42-NEXT:    [[TMP2:%.*]] = sext <2 x i16> [[TMP1]] to <2 x i64>
; SSE42-NEXT:    [[TMP3:%.*]] = bitcast i64* [[A:%.*]] to <2 x i64>*
; SSE42-NEXT:    store <2 x i64> [[TMP2]], <2 x i64>* [[TMP3]], align 4
; SSE42-NEXT:    [[ARRAYIDX5:%.*]] = getelementptr inbounds i16, i16* [[B]], i64 2
; SSE42-NEXT:    [[ARRAYIDX7:%.*]] = getelementptr inbounds i64, i64* [[A]], i64 2
; SSE42-NEXT:    [[TMP4:%.*]] = bitcast i16* [[ARRAYIDX5]] to <2 x i16>*
; SSE42-NEXT:    [[TMP5:%.*]] = load <2 x i16>, <2 x i16>* [[TMP4]], align 1
; SSE42-NEXT:    [[TMP6:%.*]] = sext <2 x i16> [[TMP5]] to <2 x i64>
; SSE42-NEXT:    [[TMP7:%.*]] = bitcast i64* [[ARRAYIDX7]] to <2 x i64>*
; SSE42-NEXT:    store <2 x i64> [[TMP6]], <2 x i64>* [[TMP7]], align 4
; SSE42-NEXT:    ret i64 undef
;
; AVX-LABEL: @test_sext_4i16_to_4i64(
; AVX-NEXT:  entry:
; AVX-NEXT:    [[TMP0:%.*]] = bitcast i16* [[B:%.*]] to <4 x i16>*
; AVX-NEXT:    [[TMP1:%.*]] = load <4 x i16>, <4 x i16>* [[TMP0]], align 1
; AVX-NEXT:    [[TMP2:%.*]] = sext <4 x i16> [[TMP1]] to <4 x i64>
; AVX-NEXT:    [[TMP3:%.*]] = bitcast i64* [[A:%.*]] to <4 x i64>*
; AVX-NEXT:    store <4 x i64> [[TMP2]], <4 x i64>* [[TMP3]], align 4
; AVX-NEXT:    ret i64 undef
;
entry:
  %0 = load i16, i16* %B, align 1
  %conv = sext i16 %0 to i64
  store i64 %conv, i64* %A, align 4
  %arrayidx2 = getelementptr inbounds i16, i16* %B, i64 1
  %1 = load i16, i16* %arrayidx2, align 1
  %conv3 = sext i16 %1 to i64
  %arrayidx4 = getelementptr inbounds i64, i64* %A, i64 1
  store i64 %conv3, i64* %arrayidx4, align 4
  %arrayidx5 = getelementptr inbounds i16, i16* %B, i64 2
  %2 = load i16, i16* %arrayidx5, align 1
  %conv6 = sext i16 %2 to i64
  %arrayidx7 = getelementptr inbounds i64, i64* %A, i64 2
  store i64 %conv6, i64* %arrayidx7, align 4
  %arrayidx8 = getelementptr inbounds i16, i16* %B, i64 3
  %3 = load i16, i16* %arrayidx8, align 1
  %conv9 = sext i16 %3 to i64
  %arrayidx10 = getelementptr inbounds i64, i64* %A, i64 3
  store i64 %conv9, i64* %arrayidx10, align 4
  ret i64 undef
}