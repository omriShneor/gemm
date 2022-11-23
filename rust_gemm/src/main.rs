use rand::Rng;
use std::time::Instant;

const N : usize = 1024;


fn main() {
    
    let mut rng = rand::thread_rng();
    let mut a = vec![vec![0u8; N]; N];
    let mut b = vec![vec![0u8; N]; N];
    let mut c = vec![vec![0u32; N]; N];

    for i in 0..a.len() {
        for j in 0..b.len(){
            a[i][j] = rng.gen::<u8>();
            b[i][j] = rng.gen::<u8>();
            c[i][j] = 0u32;
            // println!("A[{i}][{j}] {}", a[i][j]);
            // println!("B[{i}][{j}] {}", b[i][j]);
        }
    }

    let before = Instant::now();
    for i in 0..N {
        for j in 0..N {
            for k in 0..N {
                c[i][j] += (a[i][k] as u32) * (b[k][j] as u32)
            }
            // println!("C[{i}][{j}] {}", c[i][j]);
        }
    }
    println!("Elapsed time: {:.2?}", before.elapsed());
}
