fn main() {
    let stones = 202400000;
    let null_pr = 944347;
    let acol_pr = 10;

    let mut shrine_cols: Vec<i64> = vec![1];

    let mut step = 1;
    let mut pyramid = 1;
    let mut thick = 1;
    while pyramid < stones {
        step += 2;
        thick = (thick * null_pr) % acol_pr + acol_pr;
        shrine_cols = shrine_cols.iter().map(|&x| x + thick).collect::<Vec<i64>>();
        shrine_cols.push(thick);
        shrine_cols.push(thick);
        let empty = shrine_cols[..(step - 2)]
            .iter()
            .map(|&x| (null_pr * step as i64 * x) % acol_pr)
            .collect::<Vec<i64>>();
        pyramid = 2 * shrine_cols[step - 1] + shrine_cols[..(step - 2)].iter().sum::<i64>()
            - empty.iter().sum::<i64>();
    }

    println!("{} {} {}", (pyramid - stones), step, pyramid);
}
