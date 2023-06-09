# Murbay Scale

## V1.3.2

#### PLU Eklendi
```sh
PLU Save
Fiyat gir
PLU ya basılı tut 
0-99 Address gir 
Save tusuna bas	
```
```sh
PLU Call
PLU bas
Adres gir 
Save e bas(2 haneli adreslerde var )
	
```
####  Save Tusu Aktif
```sh
     * Fiyatı ekranda sabit tutar
```
#### Unit Tusu Aktif
```sh
Brim secme iconunu aktif pasif yappıyor 
```
#### Pil Seçim Aktif
```sh
Battery ölçme devresei yapılırsa aktiflesecek 
```
#### M+
```sh
RS232 modlarından 2-3 acıksa devreye giriyor 
Fiyatı yaz tartımı yap stable olmasını bekle m+ ya bas
Yukarıdakı ıslemı max 99 sefer tekrarla
```
#### QTY 
```sh
Fiyatı yaz QTY bas 
Kg YAZ
Fiyat hesaplanmış olsun
QTY basarak kapat
```
- Modellere göre ölçme aralıkları ayarlandı ama bunun için extra menu      ekledim diğerlerinin hangi kombinde ne olacağı saçma geldi anlamadım
- Yüksek ağırlık overload - -ol- -
- yüksek fiyat overload - -ol- -



## V1.3.1
- 2g 5g 10 gr stepler eklendi

## V1.3
- kg olarak okuma gerçekleştirildi !
## V1.2

- i2c geçici olarak rs232 pinleri ile değiştirildi sadece 4 numara 



## V1.1
- Ekranda fix float mantığı eksik . Float yapıldı, fix mantığı yerleştirilmedi 
- I2C Pinleri donanım olarak yok 
- Buzzer yok donanım olarak
- Led kontrol yok donanım olarak
- Geliştime status ledi donanım olarak yok 
- Extern kullanıldı. İlerleyen süreçte extern lerden kurtarılması gerek .




# Note WEAK Fx 
- This function simulated declaretion function prototip 
if declare real funtion not weak this function not running . Using just function can be defined. 
``` 
__WEAK void  SCREEN_1_AIP_ResetPin(uint8_t _val);
```