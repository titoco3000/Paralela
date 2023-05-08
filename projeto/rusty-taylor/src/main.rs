/*
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
cargo new rusty-taylor
cargo add rug

sudo apt-get install diffutils gcc m4 make
*/

//para paralelismo
use std::thread;
use crossbeam_channel;

use rug::{Float, float::Round};

const PRECISAO_FLOAT: u32 = 10000000;

fn calcular_e_paralelo_float(voltas:u32)->String{
    let (fat_sender, fat_receiver) = crossbeam_channel::unbounded::<Float>();
    let mut sum = Float::with_val(PRECISAO_FLOAT, 1.0);
    
    thread::spawn(move||{
        let mut fat = Float::with_val(PRECISAO_FLOAT, 1.0);
        let mut i = 1.0;
        let voltas = (voltas+1) as f32;
        while i < voltas{
            fat /= i;
            fat_sender.send(fat.clone()).expect("algum erro no fat");
            i+=1.0;
        }
        println!("fatorialer finished");
    });
    while let Ok(val) = fat_receiver.recv() {
        sum+=val;
    }
    println!("Produzindo arquivo (float paralelo)...");
    return sum.to_string_radix_round(10, Some(1000000), Round::Nearest);
}

fn calcular_e_serial_float(voltas: u32) ->String {
    
    let mut sum = Float::with_val(PRECISAO_FLOAT, 1.0);
    let mut fat = Float::with_val(PRECISAO_FLOAT, 1.0);
    for i in 1..voltas+1{
        fat /= i as f32;
        sum += &fat;
    }
    println!("Produzindo arquivo (float serial)...");
    return sum.to_string_radix_round(10, Some(1000000), Round::Down);
}

fn calcular_e_serial_int(voltas: u32) ->String {
    use rug::{Assign, Integer};
    let mut sum = Integer::new();
    sum.assign(Integer::i_pow_u(10, 10000000));
    let mut fat = sum.clone();
    for i in 1..voltas+1{
        fat /= i;
        sum += &fat;
    }
    println!("Produzindo arquivo (int serial)...");
    let mut sum_str = sum.to_string_radix(10);
    sum_str.insert(1,'.');
    return sum_str;
}

fn main() {
    use std::env;
    use std::fs::OpenOptions;
    use std::io::Write;

    let args: Vec<String> = env::args().collect();
    if args.len() < 4{
        println!("Argumentos insuficientes.\nPrecisa de:\n <serial OU paralelo> <float OU int> <nº etapas>") ;
        return;
    }
    let etapas = args[3].parse::<u32>().expect("Primeiro arg deve indicar etapas");
    let valor =
        if args[1].to_lowercase().starts_with("s"){ //serial
            if args[2].to_lowercase().starts_with("f"){ //float
                calcular_e_serial_float(etapas)
            }
            else{//int
                calcular_e_serial_int(etapas)
            }
        }
        else{//paralelo
            if args[2].to_lowercase().starts_with("f"){ //float
                calcular_e_paralelo_float(etapas)
            }
            else{//int
                panic!("Paralelo não implementado");
                //calcular_e_serial_int(etapas)
            }
        };
    let mut file = OpenOptions::new().write(true)
                             .truncate(true) 
                             .create(true)
                             .open("out.txt")
                             .expect("Erro ao abrir arquivo");
    file.write_all(valor.as_bytes()).expect("Erro ao escrever para o arquivo");
}
