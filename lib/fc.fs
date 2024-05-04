module fc

let about = printfn "F# compiler library"

open System

Environment.SetEnvironmentVariable(
    "PATH",
    Environment.CurrentDirectory + ":" + Environment.GetEnvironmentVariable("PATH")
)

type Token =
    | Int of int
    | Str of string

type expr =
    | Int of int
    | Op of string * expr * expr

printfn "%A" (Int 123, Op("+", Int 2, Int 3))

let rec eval (e: expr) : int =
    match e with
    | Int i -> i
    | Op("+", e1, e2) -> eval e1 + eval e2
    | _ -> failwith ""

printfn "%A" [ eval (Op("+", Int 1, Int 2)) ]
