# Murbay terazi kodu 

## V1.3.2
- Plu eklendi 
- save tusu aktif
- unit tuşu katif
- pil seçim aktif 

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