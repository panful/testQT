export function sum(subject) {
    var reg = /[\p{Han}]+/g;
    var ret = subject.match(reg);
    return ret;
}
