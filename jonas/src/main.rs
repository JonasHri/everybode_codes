use itertools::Itertools;
fn main() {
    let items = vec![0, 0, 1, 2];
    for perm in items.iter().permutations(items.len()).unique() {
        println!("{:?}", perm);
    }
}
