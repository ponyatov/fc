module fc

let about = "F# compiler library"

type expr =
    | Int of int
    | Var of string
    | Op of string * expr * expr

let i123 = Int 123
let add12 = Op("+", Int 1, Int 2)
let vasd = Var "asd"

let env: (string * int) list = [ ("pi", 3); ("zero", 0) ]

let rec lookup (env: (string * int) list) (name: string) : int =
    match env with
    | [] -> failwith name
    | (k, v) :: r -> if k = name then v else lookup r name


let rec eval (expr: expr) : int =
    match expr with
    | Int i -> i
    | Op("+", e1, e2) -> eval e1 + eval e2
    | Op("*", e1, e2) -> eval e1 * eval e2
    | _ -> failwith ""

// eval Op("+", Int 1, Int 2)
