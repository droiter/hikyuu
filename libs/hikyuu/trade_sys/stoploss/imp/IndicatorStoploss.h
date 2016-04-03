/*
 * IndicatorStoploss.h
 *
 *  Created on: 2013-4-21
 *      Author: fasiondog
 */

#ifndef INDICATORSTOPLOSS_H_
#define INDICATORSTOPLOSS_H_

#include "../../../indicator/Indicator.h"
#include "../StoplossBase.h"

namespace hku {

class IndicatorStoploss: public StoplossBase {
public:
    IndicatorStoploss(); //仅用于序列化默认构造函数
    IndicatorStoploss(const string& name, const Indicator& ind,
                      const string& kdata_part);
    virtual ~IndicatorStoploss();

    virtual string name() const;
    virtual price_t getPrice(const Datetime& datetime, price_t price);
    virtual void _reset();
    virtual StoplossPtr _clone();
    virtual void _calculate();

private:
    string    m_name;
    Indicator m_ind;
    string    m_kdata_part;
    map<Datetime, price_t> m_result;

//========================================
//序列化支持
//========================================
#if HKU_SUPPORT_SERIALIZATION
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(StoplossBase);
        ar & BOOST_SERIALIZATION_NVP(m_name);
        ar & BOOST_SERIALIZATION_NVP(m_ind);
        ar & BOOST_SERIALIZATION_NVP(m_kdata_part);
        //m_result 每次系统运行时都要重新计算，不保存
        //ar & BOOST_SERIALIZATION_NVP(m_result);
    }
#endif /* HKU_SUPPORT_SERIALIZATION */
};

} /* namespace hku */
#endif /* INDICATORSTOPLOSS_H_ */